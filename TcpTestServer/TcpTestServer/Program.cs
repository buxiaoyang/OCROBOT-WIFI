using System;
using System.Collections.Generic;
using System.Net;
using System.Net.Sockets;
using System.Text;

namespace TcpTestServer
{
    class Program
    {
        static void Main(string[] args)
        {
            Server(10086); //监听10086端口
        }

        /// <summary>
        /// 服务器端
        /// </summary>
        /// <param name="port"></param>
        static void Server(int port)
        {
            try
            {
                //1.监听端口
                TcpListener server = new TcpListener(IPAddress.Any, port);
                server.Start();
                Console.WriteLine("{0:HH:mm:ss}->监听端口{1}...", DateTime.Now, port);

                //2.等待请求
                while (true)
                {
                    try
                    {
                        //2.1 收到请求
                        TcpClient client = server.AcceptTcpClient(); //停在这等待连接请求
                        IPEndPoint ipendpoint = client.Client.RemoteEndPoint as IPEndPoint;
                        NetworkStream stream = client.GetStream();

                        //2.2 解析数据,长度<1024字节
                        string data = string.Empty;
                        byte[] bytes = new byte[1024];
                        int length = stream.Read(bytes, 0, bytes.Length);
                        if (length > 0)
                        {
                            data = Encoding.Default.GetString(bytes, 0, length);
                            Console.WriteLine("{0:HH:mm:ss}->接收数据(from {1}:{2})：{3}", DateTime.Now, ipendpoint.Address, ipendpoint.Port, data);
                        }

                        //2.3 返回状态
                        byte[] messages = Encoding.Default.GetBytes("ok.");
                        stream.Write(messages, 0, messages.Length);

                        //2.4 关闭客户端
                        stream.Close();
                        client.Close();
                    }
                    catch (Exception ex)
                    {
                        Console.WriteLine("{0:HH:mm:ss}->{1}", DateTime.Now, ex.Message);
                    }
                }
            }
            catch (SocketException socketEx)
            {
                //10013 The requested address is a broadcast address, but flag is not set.
                if (socketEx.ErrorCode == 10013)
                    Console.WriteLine("{0:HH:mm:ss}->启动失败,请检查{1}端口有无其他程序占用.", DateTime.Now, port);
                else
                    Console.WriteLine("{0:HH:mm:ss}->{1}", DateTime.Now, socketEx.Message);
            }
            catch (Exception ex)
            {
                Console.WriteLine("{0:HH:mm:ss}->{1}", DateTime.Now, ex.Message);
            }
            Console.ReadKey();
        }
    }
}
