using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using Project4_Shapes;

namespace Project4_Shapes
{
    public partial class Form1 : Form
    {
        const string MyName = "treewolf";
        Bitmap image;

        public Form1()
        {
            InitializeComponent();
            Graphics imageGraphics;
            image = new Bitmap(pictureBox1.Width, pictureBox1.Height);
            imageGraphics = Graphics.FromImage(image);
        }

        private void button1_Click(object sender, EventArgs e)
        {
            DialogResult result = openFileDialog1.ShowDialog();
            if (result == DialogResult.OK)
            {
                try
                {
                    System.IO.Stream fileStream = openFileDialog1.OpenFile();
                    List<string> shapes = new List<string>();

                    // PSEUDOCODE FOR USING STREAMREADER TO READ FROM FILE
                    // Use the above System.IO.Stream fileStream adn create a new StreamReader
                    // While the reader has more lines (you might want to look at the Peek() method), 
                    //      get the string line and assign it to a variable
                    // Add the string line to the Items collection of the listbox
                    // Add the string line to the List<string> shapes list

                    // 'using' closes StreamReader
                    using (System.IO.StreamReader sr = new System.IO.StreamReader(fileStream))
                    {
                        System.String line;
                        while ((line = sr.ReadLine()) != null)
                        {
                            listBox1.Items.Add(line);
                            shapes.Add(line);                            
                        }
                    }

                    fileStream.Close();
                    DrawImage(shapes);
                }
                catch
                {
                    MessageBox.Show("Error reading file");
                }
            }
        }

        private void DrawImage(List<string> shapes)
        {
            Graphics imageGraphics;
            imageGraphics = Graphics.FromImage(image);

            // For every shape read from the file, create the shape and call the draw method
            // You will need to pay attention to this section to create your Shape.cs class
            foreach (string shape in shapes)
            {
                string[] shapeDetails = shape.Split(',');

                //YOU MUST UNCOMMENT THE FOLLOWING LINES OF CODE AFTER YOU CREATE YOUR Shape.cs CLASS
                switch (shapeDetails[0])
                {
                    case "Triangle":
                        Shape tri = new Shape("Triangle", Color.FromName(shapeDetails[1]));
                        tri.Vertices = GetPointsFromList(GetSlice<string>(shapeDetails, 2, shapeDetails.Length - 2));
                        tri.Draw(imageGraphics);
                        Console.WriteLine(tri.ToString());
                        break;
                    case "Circle":
                        Shape cir = new Shape("Circle", Color.FromName(shapeDetails[1]));
                        cir.UpperLeft = new Point(int.Parse(shapeDetails[2]), int.Parse(shapeDetails[3]));
                        cir.Width = int.Parse(shapeDetails[4]);
                        cir.Height = int.Parse(shapeDetails[5]);
                        cir.Draw(imageGraphics);
                        Console.WriteLine(cir.ToString());
                        break;
                    case "Rectangle":
                        Shape rect = new Shape("Rectangle", Color.FromName(shapeDetails[1]));
                        rect.Vertices = GetPointsFromList(GetSlice<string>(shapeDetails, 2, shapeDetails.Length - 2));
                        rect.Draw(imageGraphics);
                        Console.WriteLine(rect.ToString());
                        break;
                    case "Polygon":
                        Shape poly = new Shape("Polygon", Color.FromName(shapeDetails[1]));
                        poly.Vertices = GetPointsFromList(GetSlice<string>(shapeDetails, 2, shapeDetails.Length - 2));
                        poly.Draw(imageGraphics);
                        Console.WriteLine(poly.ToString());
                        break;
                }
            }

            // Draw the student's name on the image
            Font myFont = new Font("Georgia", 18.0f);
            Brush myBrush = new SolidBrush(Color.DarkGoldenrod);
            imageGraphics.DrawString(MyName, myFont, myBrush, new Point(120, 320));

            pictureBox1.Image = image;

            myBrush.Dispose();
            imageGraphics.Dispose();
        }

        // helper method to convert an string array of integers to a Point[]
        private Point[] GetPointsFromList(string[] points)
        {
            points = points.Where(x => !string.IsNullOrEmpty(x)).ToArray();
            Point[] outputPoints = new Point[points.Length / 2];
            for (int i = 0; i < points.Length / 2; i++)
            {
                outputPoints[i] = new Point(int.Parse(points[i * 2]), int.Parse(points[i * 2 + 1]));
            }
            return outputPoints;
        }

        // helper method to take a slice out of an array
        static T[] GetSlice<T>(T[] array, int start, int length)
        {
            T[] result = new T[length];
            for (int i = 0; i < length; i++)
            {
                result[i] = ((start + i) < array.Length) ? array[start + i] : default(T);
            }
            return result;
        }

        private void button2_Click(object sender, EventArgs e)
        {
            // add a filter to our save filedialog to only show PNG files
            saveFileDialog1.Filter = "PNG files|*.png";
            //display save file dialog
            DialogResult result = saveFileDialog1.ShowDialog();

            if (result == DialogResult.OK)
            {
                string filePath = saveFileDialog1.FileName;
                try
                {
                    image.Save(filePath, System.Drawing.Imaging.ImageFormat.Png);
                }
                catch
                {
                    MessageBox.Show("Error writing file");
                }
            }
        }
    }
}
