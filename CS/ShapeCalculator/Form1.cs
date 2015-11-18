//
//
//  Name:       
//  Course:     MIS 15
//  Section:    01
//


using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace ShapeCalculator
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
        }

        //changes appearance and information needed for later use.
        private void shapeComboBox_SelectionChangeCommitted(object sender, EventArgs e)
        {
            String choice = shapeComboBox.Text;
            switch (choice)
            {
                case "Circle":
                    pictureBox1.Image = ShapeCalculator.Properties.Resources.circle;
                    formula.Text = "A = \u03A0r\xB2\nP = 2\u03A0r";
                    input1TextBox.Text = ""; input2TextBox.Text = "";
                    input1TextBox.Visible = true;   input2TextBox.Visible = false;  volumeLabel.Visible = false;
                    input1Label.Text = "Radius";    input2Label.Text = "";  volumeTextBox.Visible = false;
                    areaTextBox.Text = "";   perimeterTextBox.Text = "";
                    break;
                case "Rectangle":
                    pictureBox1.Image = ShapeCalculator.Properties.Resources.rectangle;
                    formula.Text = "A = lw\nP = 2l + 2w";
                    input1TextBox.Text = ""; input2TextBox.Text = "";
                    input1TextBox.Visible = true;   input2TextBox.Visible = true;   volumeLabel.Visible = false;
                    input1Label.Text = "Length";    input2Label.Text = "Width";  volumeTextBox.Visible = false;
                    areaTextBox.Text = "";   perimeterTextBox.Text = "";
                    break;
                case "Square":
                    pictureBox1.Image = ShapeCalculator.Properties.Resources.square;
                    formula.Text = "A = s\xB2\nP = 4s";
                    input1TextBox.Text = ""; input2TextBox.Text = "";
                    input1TextBox.Visible = true;   input2TextBox.Visible = false;  volumeLabel.Visible = false;
                    input1Label.Text = "Side";    input2Label.Text = "";  volumeTextBox.Visible = false;
                    areaTextBox.Text = "";   perimeterTextBox.Text = "";
                    break;
                case "Triangle (Right)":
                    pictureBox1.Image = ShapeCalculator.Properties.Resources.triangle;
                    formula.Text = "\u00BDbh\nP = b + h + \u221A (h\xB2 + b\xB2)";
                    input1TextBox.Text = ""; input2TextBox.Text = "";
                    input1TextBox.Visible = true;   input2TextBox.Visible = true;   volumeLabel.Visible = false;
                    input1Label.Text = "Base";    input2Label.Text = "Height";  volumeTextBox.Visible = false;
                    areaTextBox.Text = "";   perimeterTextBox.Text = "";
                    break;
                case "Sphere":
                    pictureBox1.Image = ShapeCalculator.Properties.Resources.sphere;
                    formula.Text = "A = 4\u03A0r\xB2\nP = 2\u03A0r\nV = \u2074\u2044\u2083\u03A0r\u00B3";
                    input1TextBox.Text = ""; input2TextBox.Text = "";
                    input1TextBox.Visible = true;   input2TextBox.Visible = false;  volumeLabel.Visible = true;
                    input1Label.Text = "Radius";    input2Label.Text = "";  volumeTextBox.Visible = true;
                    areaTextBox.Text = "";   perimeterTextBox.Text = "";
                    break;

                default:
                    input1TextBox.Visible = true;   input2TextBox.Visible = true;  volumeLabel.Visible = false;
                    input1Label.Text = "";    input2Label.Text = "";  volumeTextBox.Visible = false;
                    areaTextBox.Text = "";   perimeterTextBox.Text = "";
                    break;
            }
        }

        //Calculates the formula and outputs
        private void calculateButton_Click(object sender, EventArgs e)
        {
            //error checking
            // 1 if good
            if (errorCheck() == 1)
            {

                String choice = shapeComboBox.Text;
                double area = 0, perimeter = 0;
                switch (choice)
                {
                    case "Circle":
                        double radius = Double.Parse(input1TextBox.Text);
                        area = Math.PI * Math.Pow(radius, 2);
                        perimeter = 2 * Math.PI * radius;
                        areaTextBox.Text = area.ToString("n2"); perimeterTextBox.Text = perimeter.ToString("n2");
                        break;
                    case "Rectangle":
                        double length = Double.Parse(input1TextBox.Text); double width = Double.Parse(input2TextBox.Text);
                        area = length * width;
                        perimeter = 2 * length + 2 * width;
                        areaTextBox.Text = area.ToString("n2"); perimeterTextBox.Text = perimeter.ToString("n2");
                        break;
                    case "Square":
                        double side = Double.Parse(input1TextBox.Text);
                        area = Math.Pow(side, 2);
                        perimeter = 4 * side;
                        areaTextBox.Text = area.ToString("n2"); perimeterTextBox.Text = perimeter.ToString("n2");
                        break;
                    case "Triangle (Right)":
                        double base_tri = Double.Parse(input1TextBox.Text); double height = Double.Parse(input2TextBox.Text);
                        area = .5 * base_tri * height;
                        perimeter = base_tri + height + Math.Sqrt(Math.Pow(height, 2) + Math.Pow(base_tri, 2));
                        areaTextBox.Text = area.ToString("n2"); perimeterTextBox.Text = perimeter.ToString("n2");
                        break;
                    case "Sphere":
                        double radius_s = Double.Parse(input1TextBox.Text);
                        double volume = (4 / 3) * Math.PI * Math.Pow(radius_s, 3);
                        area = 4 * Math.PI * Math.Pow(radius_s, 2);
                        perimeter = 2 * Math.PI * radius_s;
                        areaTextBox.Text = area.ToString("n2"); perimeterTextBox.Text = perimeter.ToString("n2"); volumeTextBox.Text = volume.ToString("n2");
                        break;
                    default:

                        break;
                }
            }
            else
            {       }
            }


        //error box
        private int errorCheck(){
            string choice = shapeComboBox.Text;
            double? test = null; double? test2 = null;
            switch (choice)
            {
                case "Circle":
                    input2TextBox.Text = "0";
                    break;
                case "Rectangle":
                    break;
                case "Square":
                    input2TextBox.Text = "0";
                    break;
                case "Triangle (Right)":
                    break;
                case "Sphere":
                    input2TextBox.Text = "0";
                    break;
                default:
                    break;
            }
            //error checking

            try{
                test = Double.Parse(input1TextBox.Text);
            }
            catch(Exception g){            }
            
            try
            {
                test2 = Double.Parse(input2TextBox.Text);
            }
            catch (Exception g)           {            }
            if (test != null && test2 != null)
            {
                return 1;
            }
                else
            {
                MessageBox.Show("Invalid input. Please type only numbers as formula inputs.");
                return 0;
            }
        }
    }
}