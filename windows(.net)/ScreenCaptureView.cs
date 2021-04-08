using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace ZegoScreenCapture_.net_
{
    public partial class ScreenCaptureView : Form
    {
        Bitmap m_bitmap;

        public ScreenCaptureView()
        {
            InitializeComponent();

            //双缓冲，防止界面闪烁
            this.SetStyle(ControlStyles.OptimizedDoubleBuffer, true);
            this.SetStyle(ControlStyles.AllPaintingInWmPaint, true);
            this.SetStyle(ControlStyles.UserPaint, true);
        }

        public void setBitmap(Bitmap bmp)
        {
            m_bitmap = bmp;
            this.Invalidate();
        }

        private void ScreenCaptureView_Load(object sender, EventArgs e)
        {

        }

        private void OnPaint(object sender, PaintEventArgs e)
        {
            if (m_bitmap != null)
            {
                Graphics g = e.Graphics;
                g.DrawImage(m_bitmap, this.ClientRectangle);
            }
        }
    }
}
