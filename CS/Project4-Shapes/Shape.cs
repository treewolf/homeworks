using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Project4_Shapes
{
    class Shape : GenericShape
    {
        // global vars
        System.String name;
        System.Drawing.Color color;
        System.Drawing.Point point;

        // class constructor (step 3)
        public Shape(System.String name, System.Drawing.Color color)
        {
            this.name = name;
            this.color = color;
        }

        // additional properties of Shape class (step 4)
        public System.Drawing.Color Color
        {
            get
            {
                return color;
            }
            set
            {
                this.color = value;
            }
        }

        public System.Drawing.Point UpperLeft
        {
            get
            {
                return point;
            }
            set
            {
                this.point = value;
            }
        }

        // implement Draw() (step 5)
        public void Draw(System.Drawing.Graphics image)
        {
            System.Drawing.Brush brush = new System.Drawing.SolidBrush(color);
            System.Drawing.Pen pen = new System.Drawing.Pen(color);

            // Determine if circle, since use [upperLeft, width, height, !vertices] only
            if (name.Equals("Circle"))
            {
                image.DrawEllipse(pen, UpperLeft.X, UpperLeft.Y, Height, Width);
                image.FillEllipse(brush, new System.Drawing.Rectangle(UpperLeft.X, UpperLeft.Y, Width, Height));
            }
            else
            {
                image.DrawPolygon(pen, Vertices);
                image.FillPolygon(brush, Vertices);
            }

            brush.Dispose();
            pen.Dispose();
        }

        // override the ToString() (step 6)
        public override string ToString()
        {
            return System.String.Format("My {0} is a beautiful shade of {1}", name, color.Name);
        }
    }
}
