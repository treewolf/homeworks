using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Project4_Shapes
{
    public class GenericShape
    {
        public GenericShape()
        {
        }
        string Name { get; set; }

        public Point[] Vertices { get; set; }

        public int Width { get; set; }

        public int Height { get; set; }
    }
}
