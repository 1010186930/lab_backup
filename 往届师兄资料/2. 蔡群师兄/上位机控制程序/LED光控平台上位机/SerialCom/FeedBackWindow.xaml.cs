using Microsoft.Win32;
using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Shapes;
//反馈窗口
namespace SerialCom
{
    /// <summary>
    /// FeedBackWindow.xaml 的交互逻辑
    /// </summary>
    public partial class FeedBackWindow : Window
    {
        public FeedBackWindow()
        {
            InitializeComponent();//初始化控件
        }

        private void Image_PreviewMouseDown(object sender, MouseButtonEventArgs e)//QQ图标点击事件
        {
            try
            {
                System.Diagnostics.Process.Start("tencent://Message/?Uin=45213212");
            }
            catch
            {
                MessageBox.Show("无法调用腾讯QQ！");
            }
        }

        private void Image_PreviewMouseDown_1(object sender, MouseButtonEventArgs e)
        {
            try//调用默认浏览器打开网页
            {
                //System.Diagnostics.Process.Start("explorer.exe", "http://weibo.com/lincolne");//使用资源管理器应该会自动转到默认浏览器
                RegistryKey key = Registry.ClassesRoot.OpenSubKey("http\\shell\\open\\command", false);
                String path = key.GetValue("").ToString();
                if (path.Contains("\""))
                {
                    path = path.TrimStart('"');
                    path = path.Substring(0, path.IndexOf('"'));
                }
                key.Close();
                Process.Start(path, "http://www.wzyang.com/");
            }
            catch
            {
                MessageBox.Show("无法调用浏览器！");
            }

        }

     
         


         private void Image_MouseEnter(object sender, MouseEventArgs e)
         {
             weibo.Margin = new Thickness(0, 0, 50, 25);//图标上升25px
             weibo.Cursor = Cursors.Hand;//鼠标变为手型
         }

         private void Image_MouseLeave(object sender, MouseEventArgs e)
         {
             weibo.Margin = new Thickness(0, 0, 50, 0);//图标下降25px
         }

        private void TextBox_TextChanged(object sender, TextChangedEventArgs e)
        {

        }
    }
    }

