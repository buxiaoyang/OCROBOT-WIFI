using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Net;
using System.Net.Sockets;
using System.Text;
using System.Windows.Forms;

namespace TcpTestClient
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
        }

        private void button1_Click(object sender, EventArgs e)
        {
            /*
            this.button1.Enabled = false;
            TcpClient client = new TcpClient(this.textBoxIP.Text.Trim(), int.Parse(this.textBoxPort.Text.Trim()));
            NetworkStream stream = client.GetStream();
            byte[] send = Encoding.ASCII.GetBytes(this.textBoxDataSend.Text.Trim());
            stream.Write(send, 0, send.Length);
            byte[] bytes = new byte[client.ReceiveBufferSize];
            int count = stream.Read(bytes, 0, (int)client.ReceiveBufferSize);
            String data = Encoding.ASCII.GetString(bytes);
            char[] unused = { (char)data[count] };
            //Console.WriteLine(data.TrimEnd(unused));
            this.textBoxDataReceive.Text = data.TrimEnd(unused);
            stream.Close();
            client.Close();
            this.button1.Enabled = true;
             * */
            Client(this.textBoxIP.Text.Trim(), int.Parse(this.textBoxPort.Text.Trim()), this.textBoxDataSend.Text.Trim());
        }

        /// <summary>
        /// 客户端
        /// </summary>
        /// <param name="ip"></param>
        /// <param name="port"></param>
        /// <param name="message"></param>
        void Client(string ip, int port, string message)
        {
            try
            {
                StringBuilder RequestHeaders = new StringBuilder();
                //1.发送数据                
                TcpClient client = new TcpClient(ip, port);
                IPEndPoint ipendpoint = client.Client.RemoteEndPoint as IPEndPoint;
                NetworkStream stream = client.GetStream();
                byte[] messages = Encoding.Default.GetBytes(message);
                stream.Write(messages, 0, messages.Length);
                //Console.WriteLine("{0:HH:mm:ss}->发送数据(to {1})：{2}", DateTime.Now, ip, message);

                //2.接收状态,长度<1024字节
                byte[] bytes = new Byte[1024];
                string data = string.Empty;
                int length = stream.Read(bytes, 0, bytes.Length);
                if (length > 0)
                {
                    data = Encoding.Default.GetString(bytes, 0, length);
                    //Console.WriteLine("{0:HH:mm:ss}->接收数据(from {1}:{2})：{3}", DateTime.Now, ipendpoint.Address, ipendpoint.Port, data);

                    this.textBoxDataReceive.Text = this.textBoxDataReceive.Text + "\n" + String.Format("{0:HH:mm:ss} ({1}:{2})：{3}", DateTime.Now, ipendpoint.Address, ipendpoint.Port, data); ;
                }

                //3.关闭对象
                stream.Close();
                client.Close();
            }
            catch (Exception ex)
            {
                //Console.WriteLine("{0:HH:mm:ss}->{1}", DateTime.Now, ex.Message);
                this.textBoxDataReceive.Text = this.textBoxDataReceive.Text + "\n" + String.Format("{0:HH:mm:ss}->{1}", DateTime.Now, ex.Message);
            }
            //Console.ReadKey();
        }

    }
}
