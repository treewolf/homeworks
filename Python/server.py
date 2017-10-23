#python2.7
#csc138
#tcp web server


import datetime
import os
import re
from socket import *

#____DEFINE SERVER SETTINGS_____________________________________________________

#set host and port for server to listen on
host = '127.0.0.1'         
port = 8888   

#filesystem for server. Recommended to keep default, with server file outside dir serving pages
root = os.getcwd()+'/www'  

#____FUNCTIONS________________________________________________________________

#determine if file exists, within root dir
#directory security
def fileExists(filename):
	file = os.path.realpath(root+filename)	#real path returns absolute pathname. eg root/www/../ => root/
	return (os.path.commonprefix([file, root]) == root and os.path.exists(file))	#see if file and root directory has same directory= root dir. and file exist	

#get current date and time
def request_datetime():
	return datetime.datetime.now().strftime("%m-%d-%Y %H:%M:%S")

#404 file not found
#server simple file not found
def status_404(conn, filename):
	print '--invalid file: ' + filename 
	conn.send('HTTP/1.1 404 Not Found\r\n')
	conn.send('Host: ' + root + ': %d\r\n' % port)
	conn.send('Date: %s\r\n' % request_datetime())
	conn.send('\r\n')
	#conn.send('HTTP/1.1 404 Not Found\r\nHost: ' + root + ': %d\r\nDate: ' + request_datetime() + '\r\n\r\n' % port)
	conn.send('<html><head><title>Not Found</title></head><body>404 Not Found</body></html>\n')

#GET request
#file check here, since this is special for GET
#recieves request and returns result
def request_GET(conn, request_body):
	if fileExists(request_body):
		file = open(root+request_body, 'rb') #opens file for reading as binary, don't need absolute path since fileExists() verifies already		

		#serve http header- header must end with CRLF. /r-carriage ret /n-line feed
        	# header + empty line + data    SEE NOTES
       		conn.send('HTTP/1.1 200 OK\r\n')
        	conn.send('Host: ' + root + ': %d\r\n' % port)
        	conn.send('Date: %s\r\n' % request_datetime())
        	conn.send('\r\n') 
	#	conn.send('HTTP/1.1 200 OK\r\nContent-Type: text/html\r\nHost: ' + root + ': %d\r\nDate: ' + request_datetime() + '\r\n\r\n' % port)

        	#if file is bigger than 1024, read, else subtract and send remaining bytes, repeat
        	file.seek(0, 2)         #get fd relative to end of file, starting at byte 0
        	file_size = file.tell() #file.tell() returns current fd
        	file.seek(0)            #reset fd to beginning of file
        	byte_size = 1024                #set byte size limit to read
                                              
        	#uncomment for debugging filze size and fd
        	#print 'file_size %d, file seek  %d' % (file_size, file.tell())
                                              
        	#true as long as remaining bytes is at least byte size 
        	while file_size-file.tell() >= byte_size :
                	file_stream = file.read(byte_size)
                	conn.send(file_stream)        
                	print '--sending full bytes'  
                                           
        	#clean up after while loop, determine if has bytes else continue 
        	if file_size-file.tell() > 0:         
                	file_stream = file.read(file_size-file.tell());
                	conn.send(file_stream)        
                	print '--end of file'
		file.close()
	else:
		#send 404
		status_404(conn, request_body)


#should only accept POST, GET, HEAD, PUT -max 4 char, min 3 char
#routes data to specific request.method
def parseData(conn, data):
	#if regex finds GET in first, then serve get method
	m = re.search(r'.*HTTP/1.1', data, re.S|re.M)
	req_method = m.group()[:4].strip()
	req_body = m.group()[4:-9]
	if req_body is None or req_body == '/':		#if no body, assume is GET request and return index.html
		request_GET(conn, '/index.html')
	elif req_method == 'GET':
		request_GET(conn, req_body)	
	else:
		print 'Methods other than GET are not supported' #send 404	
		status_404(conn)
	return

#_______START HERE__________________________________________________________________

print 'root folder is %s' % root

serverSocket = socket(AF_INET, SOCK_STREAM)
serverSocket.setsockopt(SOL_SOCKET, SO_REUSEADDR, 1)	#reuse socket
serverSocket.bind((host, port))				#bind host and port
serverSocket.listen(1)					#maximum queued from clients
print 'The server is ready on %s:%d' % (host, port)

while 1:

	conn, addr = serverSocket.accept()	#sets client and client.address
	print '\nClient connected: ', addr

	# get data from request
	data = conn.recv(4096)
	
	#where all the action is routed
	parseData(conn, data)	
	
	#close connection, non persistent
	print 'socket closed: client ', addr
	conn.close()

#server shuts down, shutdown releases connection faster, for some reason socket may not be release quick
serverSocket.shutdown()
serverSocket.close()


#__NOTES________________________________________________________________________
# http header require strict format of CRLF. Dont forget the newline needs a carriage return too!
# https://en.wikipedia.org/wiki/HTTP_message_body
# https://en.wikipedia.org/wiki/List_of_HTTP_header_fields#Size_limits
# comment out comments later if professor doesn't want them, keep for debugging
# python regex: https://www.tutorialspoint.com/python/python_reg_expressions.htm
#
