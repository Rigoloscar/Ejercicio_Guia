using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using System.Net;
using System.Net.Sockets;

namespace WindowsFormsApplication1
{
    public partial class Form1 : Form
    {
        Socket server;

        public Form1()
        {
            InitializeComponent();
        }

        private void Form1_Load(object sender, EventArgs e)
        {
           
        }

        private void enviar_Click(object sender, EventArgs e)
        {

            // Queremos saber la longitud del nombre
            if (Longitud.Checked)
            {
                string mensaje = "1/" + nombre.Text;

                // Enviamos al servidor el nombre tecleado
                byte[] msg = System.Text.Encoding.ASCII.GetBytes(mensaje);
                server.Send(msg);

                //Recibimos la respuesta del servidor
                byte[] msg2 = new byte[80];
                server.Receive(msg2);
                mensaje = Encoding.ASCII.GetString(msg2).Split('\0')[0];
                MessageBox.Show(mensaje);
            }
            // Quiere saber si el nombre es bonito
            else if (Bonito.Checked)
            {
                string mensaje = "2/" + nombre.Text;

                // Enviamos al servidor el nombre tecleado
                byte[] msg = System.Text.Encoding.ASCII.GetBytes(mensaje);
                server.Send(msg);

                //Recibimos la respuesta del servidor
                byte[] msg2 = new byte[80];
                server.Receive(msg2);
                mensaje = Encoding.ASCII.GetString(msg2).Split('\0')[0];

                MessageBox.Show(mensaje);
            }
            else if (Altura.Checked)
            {
                string mensaje = "3/" + nombre.Text + "/" + altura_box.Text;

                // Enviamos al servidor el nombre tecleado y la altura
                byte[] msg = System.Text.Encoding.ASCII.GetBytes(mensaje);
                server.Send(msg);

                //Recibimos la respuesta del servidor
                byte[] msg2 = new byte[80];
                server.Receive(msg2);
                mensaje = Encoding.ASCII.GetString(msg2).Split('\0')[0];

                MessageBox.Show(mensaje);

            }
            else if (Mayusculas.Checked)
            {
                string mensaje = "4/" + nombre.Text;

                // Enviamos al servidor el nombre tecleado y la altura
                byte[] msg = System.Text.Encoding.ASCII.GetBytes(mensaje);
                server.Send(msg);

                //Recibimos la respuesta del servidor
                byte[] msg2 = new byte[80];
                server.Receive(msg2);
                mensaje = Encoding.ASCII.GetString(msg2).Split('\0')[0];

                MessageBox.Show(mensaje);

            }
            else if (Palindromo.Checked)
            {
                string mensaje = "5/" + nombre.Text;

                // Enviamos al servidor el nombre tecleado y la altura
                byte[] msg = System.Text.Encoding.ASCII.GetBytes(mensaje);
                server.Send(msg);

                //Recibimos la respuesta del servidor
                byte[] msg2 = new byte[80];
                server.Receive(msg2);
                mensaje = Encoding.ASCII.GetString(msg2).Split('\0')[0];

                MessageBox.Show(mensaje);

            }
        }

        private void connectar_Click(object sender, EventArgs e)
        {
            // Creamos un IPEndPoint con el ip del servidor y puerto del servidor al que deseamos conectarnos (192.168.1.37 en nuestro caso)
            IPAddress direc = IPAddress.Parse("192.168.1.37");
            IPEndPoint ipep = new IPEndPoint(direc, 9050);

            // Creamos el socket 
            server = new Socket(AddressFamily.InterNetwork, SocketType.Stream, ProtocolType.Tcp);

            // Intentamos conectar el socket
            try
            {
                server.Connect(ipep);
                this.BackColor = Color.Green;
            }
            // En caso de excepción
            catch (SocketException)
            {
                MessageBox.Show("No se ha podido conectar con el servidor");
                return;
            }
        }

        private void desconectar_Click(object sender, EventArgs e)
        {
            // Mensaje de desconnexión
            string mensaje = "0/";

            byte[] msg = System.Text.Encoding.ASCII.GetBytes(mensaje);
            server.Send(msg);

            // Nos desconectamos
            this.BackColor = Color.Gray;
            server.Shutdown(SocketShutdown.Both);
            server.Close();
        }
    }
}
