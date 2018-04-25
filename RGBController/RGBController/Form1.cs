using System;
using System.IO.Ports;
using System.Drawing;
using System.Windows.Forms;
using RGBController.Properties;

namespace RGBController
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
        }
        SerialPort port = new SerialPort("COM1", 115200);
        private void Form1_Load(object sender, EventArgs e)
        {
            for (int i = 1; i <= 20; i++)
            {
                comboBox1.Items.Add("COM" + i.ToString());
            }
            comboBox1.SelectedIndex = 0;           
        }

        private async void comboBox1_SelectedIndexChanged(object sender, EventArgs e)
        {
            port.Close();
            port.PortName = comboBox1.SelectedItem.ToString();
            try
            {
                port.Open();
            }
            catch (Exception)
            {
                if (comboBox1.SelectedIndex > 18) comboBox1.SelectedIndex = 0;
                else comboBox1.SelectedIndex++;
            }
            port.WriteLine("ping");
            
        }
        private void changeColor(object sender, EventArgs e)
        {
            panel1.BackColor = Color.FromArgb(trackBar3.Value, trackBar2.Value, trackBar1.Value);
            label7.Text = trackBar3.Value.ToString();
            label6.Text = trackBar2.Value.ToString();
            label5.Text = trackBar1.Value.ToString();
            label10.Text = trackBar4.Value.ToString();
            label11.Text = trackBar5.Value.ToString();
        }

        private void comboBox1_DropDown(object sender, EventArgs e)
        {
            string[] ports = SerialPort.GetPortNames();
            comboBox1.Items.Clear();
            foreach (string comport in ports)
            {
                comboBox1.Items.Add(comport);
            }
        }
        void functionA()
        {
            port.WriteLine("sta");
        }
        void functionB()
        {
            port.WriteLine("bli");
        }
        void functionC()
        {
            port.WriteLine("bre");
        }
        void functionD()
        {
            port.WriteLine("rac");
        }

        private void button5_Click(object sender, EventArgs e)
        {
            functionS();
        }
        void functionS()
        {
            port.WriteLine("s");
        }
        void send_custom_color()
        {
            if (checkBox3.Checked == true)
            {
                string hex = ("c 0x") + trackBar2.Value.ToString("X2") + trackBar3.Value.ToString("X2") + trackBar1.Value.ToString("X2");
                port.WriteLine(hex);
            }
            if (checkBox1.Checked == true)
            {
                port.WriteLine("T1" + trackBar3.Value.ToString() + "R" + trackBar2.Value.ToString() + "G" + trackBar1.Value.ToString() + "B");
            }
            if (checkBox2.Checked == true)
            {
                port.WriteLine("T2" + trackBar3.Value.ToString() + "R" + trackBar2.Value.ToString() + "G" + trackBar1.Value.ToString() + "B");
            }
            if (checkBox4.Checked == true)
            {
                port.WriteLine("T3" + trackBar3.Value.ToString() + "R" + trackBar2.Value.ToString() + "G" + trackBar1.Value.ToString() + "B");
            }
        }
        void send_custom_speed()
        {
            if (checkBox3.Checked == true)
            {
                string speed = ("s ") + trackBar5.Value.ToString();
                port.WriteLine(speed);
            }
        }
        void send_custom_brightness()
        {
            if (checkBox3.Checked == true)
            {
                string brightness = ("b ") + trackBar4.Value.ToString();
                port.WriteLine(brightness);
            }
        }
        private void trackBar3_MouseUp(object sender, MouseEventArgs e)
        {
            send_custom_color();
        }

        private void trackBar2_MouseUp(object sender, MouseEventArgs e)
        {
            send_custom_color();
        }

        private void trackBar1_MouseUp(object sender, MouseEventArgs e)
        {
            send_custom_color();
        }

        private void button6_Click(object sender, EventArgs e)
        {
            functionX();
        }
        void functionX()
        {
            port.WriteLine("x");
        }

        private void trackBar3_ValueChanged(object sender, EventArgs e)
        {
            send_custom_color();
        }

        private void trackBar2_ValueChanged(object sender, EventArgs e)
        {
            send_custom_color();
        }

        private void trackBar1_ValueChanged(object sender, EventArgs e)
        {
            send_custom_color();
        }
        void functionE()
        {
            port.WriteLine("rai");
        }
        void functionG()
        {
            port.WriteLine("blr");
        }

        private void trackBar5_ValueChanged(object sender, EventArgs e)
        {
            send_custom_speed();
        }

        private void trackBar4_ValueChanged(object sender, EventArgs e)
        {
            send_custom_brightness();
        }

        private void Form1_FormClosing(object sender, FormClosingEventArgs e)
        {
            Settings.Default["Brightness"] = trackBar4.Value;
            Settings.Default["Speed"] = trackBar5.Value;
            Settings.Default["RedColor"] = trackBar3.Value;
            Settings.Default["GreenColor"] = trackBar2.Value;
            Settings.Default["BlueColor"] = trackBar1.Value;
            Settings.Default.Save(); 
        }

        private void Form1_Load_1(object sender, EventArgs e)
        {
            panel1.BackColor = Color.FromArgb(trackBar3.Value, trackBar2.Value, trackBar1.Value);
            label7.Text = trackBar3.Value.ToString();
            label6.Text = trackBar2.Value.ToString();
            label5.Text = trackBar1.Value.ToString();
            label10.Text = trackBar4.Value.ToString();
            label11.Text = trackBar5.Value.ToString(); 
            if (checkBox1.Checked == false && checkBox2.Checked == false && checkBox3.Checked == false)
            {
                comboBox2.Hide();
                comboBox3.Hide();
            }
            label8.Hide();
            label9.Hide();
            label10.Hide();
            label11.Hide();
            trackBar4.Hide();
            trackBar5.Hide();
            label2.Hide();
            label3.Hide();
            label4.Hide();
            label5.Hide();
            label6.Hide();
            label7.Hide();
            trackBar1.Hide();
            trackBar2.Hide();
            trackBar3.Hide();
        }

        private void comboBox2_SelectedIndexChanged(object sender, EventArgs e)
        {
            if (comboBox2.SelectedItem == "Static")
            {
                trackBar5.Hide();
                label9.Hide();
                label11.Hide();
                functionA();
            }
            if (comboBox2.SelectedItem == "Blink")
            {
                trackBar5.Show();
                label9.Show();
                label11.Show();
                trackBar5.Minimum = 250;
                functionB();
            }
            if (comboBox2.SelectedItem == "Breath")
            {
                trackBar5.Show();
                label9.Show();
                label11.Show();
                trackBar5.Minimum = 10;
                functionC();
            }
            if (comboBox2.SelectedItem == "Random")
            {
                trackBar5.Show();
                label9.Show();
                label11.Show();
                trackBar5.Minimum = 250;
                functionD();
            }
            if (comboBox2.SelectedItem == "Rainbow")
            {
                trackBar5.Show();
                label9.Show();
                label11.Show();
                trackBar5.Minimum = 10;
                functionE();
            }
            if (comboBox2.SelectedItem == "Rainbow Blink")
            {
                trackBar5.Show();
                label9.Show();
                label11.Show();
                trackBar5.Minimum = 250;
                functionG();
            }
        }

        private void checkBox1_CheckedChanged(object sender, EventArgs e)
        {
            if(checkBox1.Checked == true)
            {
                comboBox2.Hide();
                comboBox3.Hide();
                checkBox2.Enabled = false;
                checkBox4.Enabled = false;
                checkBox2.Checked = false;
                checkBox4.Checked = false;
                checkBox3.Checked = false;
                checkBox3.Enabled = false;
                label8.Hide();
                label9.Hide();
                label10.Hide();
                label11.Hide();
                trackBar4.Hide();
                trackBar5.Hide();
                label2.Show();
                label3.Show();
                label4.Show();
                label5.Show();
                label6.Show();
                label7.Show();
                trackBar1.Show();
                trackBar2.Show();
                trackBar3.Show();
            }
            if (checkBox1.Checked == false)
            {
                label2.Hide();
                label3.Hide();
                label4.Hide();
                label5.Hide();
                label6.Hide();
                label7.Hide();
                trackBar1.Hide();
                trackBar2.Hide();
                trackBar3.Hide();
                checkBox2.Enabled = true;
                checkBox4.Enabled = true;
                checkBox3.Enabled = true;
            }
        }

        private void checkBox2_CheckedChanged(object sender, EventArgs e)
        {
            if(checkBox2.Checked == true)
            {
                comboBox2.Hide();
                comboBox3.Hide();
                checkBox1.Enabled = false;
                checkBox4.Enabled = false;
                checkBox1.Checked = false;
                checkBox4.Checked = false;
                checkBox3.Checked = false;
                checkBox3.Enabled = false;
                label8.Hide();
                label9.Hide();
                label10.Hide();
                label11.Hide();
                trackBar4.Hide();
                trackBar5.Hide();
                label2.Show();
                label3.Show();
                label4.Show();
                label5.Show();
                label6.Show();
                label7.Show();
                trackBar1.Show();
                trackBar2.Show();
                trackBar3.Show();
            }
            if (checkBox2.Checked == false)
            {
                label2.Hide();
                label3.Hide();
                label4.Hide();
                label5.Hide();
                label6.Hide();
                label7.Hide();
                trackBar1.Hide();
                trackBar2.Hide();
                trackBar3.Hide();
                checkBox1.Enabled = true;
                checkBox4.Enabled = true;
                checkBox3.Enabled = true;
            }
        }

        private void checkBox3_CheckedChanged(object sender, EventArgs e)
        {
            if (checkBox3.Checked == true)
            {
                comboBox2.Show();
                comboBox3.Hide();
                checkBox1.Checked = false;
                checkBox2.Checked = false;
                checkBox4.Checked = false;
                checkBox1.Enabled = false;
                checkBox2.Enabled = false;
                checkBox4.Enabled = false;
                label8.Show();
                label9.Show();
                label10.Show();
                label11.Show();
                trackBar4.Show();
                trackBar5.Show();
                label2.Show();
                label3.Show();
                label4.Show();
                label5.Show();
                label6.Show();
                label7.Show();
                trackBar1.Show();
                trackBar2.Show();
                trackBar3.Show();
            }
            if (checkBox3.Checked == false)
            {
                checkBox1.Enabled = true;
                checkBox2.Enabled = true;
                checkBox4.Enabled = true;
                comboBox2.Hide();
                comboBox3.Hide();
                label8.Hide();
                label9.Hide();
                label10.Hide();
                label11.Hide();
                trackBar4.Hide();
                trackBar5.Hide();
                label2.Hide();
                label3.Hide();
                label4.Hide();
                label5.Hide();
                label6.Hide();
                label7.Hide();
                trackBar1.Hide();
                trackBar2.Hide();
                trackBar3.Hide();
            }
        }

        private void comboBox3_SelectedIndexChanged(object sender, EventArgs e)
        {
            if (comboBox3.SelectedItem == "Static")
            {
                label2.Show();
                label3.Show();
                label4.Show();
                label5.Show();
                label6.Show();
                label7.Show();
                trackBar1.Show();
                trackBar2.Show();
                trackBar3.Show();
                send_custom_color();
            }
            if (comboBox3.SelectedItem == "Rainbow")
            {
                label2.Hide();
                label3.Hide();
                label4.Hide();
                label5.Hide();
                label6.Hide();
                label7.Hide();
                trackBar1.Hide();
                trackBar2.Hide();
                trackBar3.Hide();
                port.WriteLine("trb");
            }
            if (comboBox3.SelectedItem == "Fade 1")
            {
                label2.Hide();
                label3.Hide();
                label4.Hide();
                label5.Hide();
                label6.Hide();
                label7.Hide();
                trackBar1.Hide();
                trackBar2.Hide();
                trackBar3.Hide();
                port.WriteLine("TF");
            }
            if (comboBox3.SelectedItem == "Fade 2")
            {
                label2.Hide();
                label3.Hide();
                label4.Hide();
                label5.Hide();
                label6.Hide();
                label7.Hide();
                trackBar1.Hide();
                trackBar2.Hide();
                trackBar3.Hide();
                port.WriteLine("TFR");
            }
            if (comboBox3.SelectedItem == "Random Fade")
            {
                label2.Hide();
                label3.Hide();
                label4.Hide();
                label5.Hide();
                label6.Hide();
                label7.Hide();
                trackBar1.Hide();
                trackBar2.Hide();
                trackBar3.Hide();
                port.WriteLine("TRA");
            }
            if (comboBox3.SelectedItem == "Off")
            {
                label2.Hide();
                label3.Hide();
                label4.Hide();
                label5.Hide();
                label6.Hide();
                label7.Hide();
                trackBar1.Hide();
                trackBar2.Hide();
                trackBar3.Hide();
                port.WriteLine("TOFF");
            }
        }

        private void checkBox4_CheckedChanged(object sender, EventArgs e)
        {
            if (checkBox4.Checked == true)
            {
                comboBox3.Show();
                checkBox1.Enabled = false;
                checkBox2.Enabled = false;
                checkBox3.Enabled = false;
                checkBox1.Checked = false;
                checkBox2.Checked = false;
                checkBox3.Checked = false;
            }
            if (checkBox4.Checked == false)
            {
                label2.Hide();
                label3.Hide();
                label4.Hide();
                label5.Hide();
                label6.Hide();
                label7.Hide();
                trackBar1.Hide();
                trackBar2.Hide();
                trackBar3.Hide();
                checkBox1.Enabled = true;
                checkBox2.Enabled = true;
                checkBox3.Enabled = true;
            }
        }
    }
}
