using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Collections.Generic;
using System.Linq;
using System.Text;

using System.Windows.Forms;

namespace JigSample
{
    class Class1
    {
        public static string[] GetFiles()
        {
            OpenFileDialog dlg = new OpenFileDialog();
            dlg.Multiselect = true;//等于true表示可以选择多个文件
            dlg.DefaultExt = ".txt";
            dlg.Filter = "cad文件|*.dwg";
            if (dlg.ShowDialog() == DialogResult.OK)
            {
                return dlg.FileNames;
                //foreach (string file in dlg.FileNames)
            }
            return new String[0];
        }
    }
}
