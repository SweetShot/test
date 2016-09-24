using System;
using System.IO;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace MyNote
{
    public partial class Form1 : Form
    {
        String username;
        String password;

        public Form1()
        {
            InitializeComponent();
        }

        private void button1_Click(object sender, EventArgs e)
        {
            this.username = txtUser.Text;
            this.password = txtPass.Text;

            // Check username and password
            try
            {   // Open the text file using a stream reader.
                using (StreamReader sr = new StreamReader("data.txt"))
                {
                    // Read the stream to a string, and write the string to the console.
                    String line = sr.ReadLine();
                    if(!line.Equals(username))
                    {
                        MessageBox.Show("Username not valid.");
                        return; 
                    }
                    line = sr.ReadLine();
                    if (!line.Equals(password))
                    {
                        MessageBox.Show("Password not valid.");
                        return;
                    }

                    MessageBox.Show("Login Successfull.");

                }
            }
            catch (Exception ex)
            {
                Console.WriteLine("The file could not be read:");
                Console.WriteLine(ex.Message);
            }
        }

    }
}
