using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.Threading;

namespace chessGraphics
{
    public partial class Form1 : Form
    {
        

        private Square srcSquare;
        private Square dstSquare;

        private pipe enginePipe;
        Button[,] matBoard;

        bool isCurPlWhite = true;
        bool isGameOver = false;

        bool isDarkTheme = true;
        Color darkBackground = Color.FromArgb(18, 18, 18);
        Color darkWhiteSquare = Color.FromArgb(220, 220, 220);
        Color darkBlackSquare = Color.FromArgb(46, 46, 46);
        Color darkBorder = Color.FromArgb(34, 34, 34);
        Color darkText = Color.FromArgb(224, 224, 224);

        Color lightBackground = Color.White;
        Color lightWhiteSquare = Color.FromArgb(240, 240, 240);
        Color lightBlackSquare = Color.FromArgb(160, 160, 160);
        Color lightBorder = Color.Gray;
        Color lightText = Color.Black;

        const int BOARD_SIZE = 8;

        public Form1()
        {
            InitializeComponent();
            ApplyTheme();
        }

        private void initForm()
        {
            enginePipe.connect();

            Invoke((MethodInvoker)delegate {  

                lblWaiting.Visible = false;
                lblCurrentPlayer.Visible = true;
                label1.Visible = true;

                        

                string s = enginePipe.getEngineMessage();

                if (s.Length != (BOARD_SIZE * BOARD_SIZE + 1))
                {
                    MessageBox.Show("The length of the board's string is not according the PROTOCOL");
                    this.Close();

                }
                else
                {
                    isCurPlWhite = (s[s.Length - 1] == '0');
                    paintBoard(s);
                }

            });
    
        }

        Thread connectionThread;
        private void Form1_Load(object sender, EventArgs e)
        {
            enginePipe = new pipe();
            //this.Show();
            
            //MessageBox.Show("Press OK to start waiting for engine to connect...");
            connectionThread = new Thread(initForm);
            connectionThread.Start();
            connectionThread.IsBackground = true;
            
            //initForm();
        
        }

        Image getImageBySign(char sign)
        {
            switch (sign)
            {
                case 'Q':
                    return Properties.Resources.q_black;
                case 'q':
                    return Properties.Resources.q_white;
                case 'K':
                    return Properties.Resources.k_black;
                case 'k':
                    return Properties.Resources.k_white;
                case 'P':
                    return Properties.Resources.p_black;
                case 'p':
                    return Properties.Resources.p_white;
                case 'R':
                    return Properties.Resources.r_black;
                case 'r':
                    return Properties.Resources.r_white;
                case 'N':
                    return Properties.Resources.n_black;
                case 'n':
                    return Properties.Resources.n_white;
                case 'B':
                    return Properties.Resources.b_black;
                case 'b':
                    return Properties.Resources.b_white;
                case '#':
                    return null;
                default:
                    return Properties.Resources.x;

            }
        }

        private void paintBoard(string board)
        {
            int i, j, z=0;

            matBoard = new Button[BOARD_SIZE, BOARD_SIZE];

            btnBoard.FlatAppearance.MouseOverBackColor = Color.LightGray;
            
            Button newBtn;
            Point pnt;

            int currentWidth = btnBoard.Location.X;
            int currentHeight = btnBoard.Location.Y;
            
            bool isColBlack = true;
            bool isRowBlack = true ;
            
            this.SuspendLayout();

            lblCurrentPlayer.Text = isCurPlWhite ? "White" : "Black";

            for (i = 0; i < BOARD_SIZE; i++)
            {
                currentWidth = btnBoard.Location.X;
                isColBlack = isRowBlack;

                for (j = 0; j < BOARD_SIZE; j++)
                {
                    newBtn = new Button();
                    matBoard[i, j] = newBtn;

                    newBtn.FlatAppearance.MouseOverBackColor = btnBoard.FlatAppearance.MouseOverBackColor ;
                    newBtn.BackColor = isColBlack ? Color.FromArgb(220, 220, 220) : Color.FromArgb(46, 46, 46);
                    newBtn.FlatAppearance.BorderColor = Color.FromArgb(68, 68, 68);
                    newBtn.FlatAppearance.BorderSize = btnBoard.FlatAppearance.BorderSize;
                    newBtn.FlatStyle = btnBoard.FlatStyle;

                    newBtn.Size = new System.Drawing.Size(btnBoard.Width, btnBoard.Height);
                    newBtn.Tag = new Square(i, j);
                    pnt = new Point(currentWidth, currentHeight );
                    newBtn.Location = pnt;
                    newBtn.BackgroundImageLayout = ImageLayout.Stretch;

                    newBtn.BackgroundImage  = getImageBySign(board[z]);
                    
                    newBtn.Click += lastlbl_Click;

                    Controls.Add(newBtn);


                    currentWidth += btnBoard.Width;
                    isColBlack = !isColBlack;
                    z++;

                }

                isRowBlack = !isRowBlack;
                currentHeight += btnBoard.Height;

            }


            Controls.Remove(btnBoard);
            this.ResumeLayout(false);
        }

        void lastlbl_Click(object sender, EventArgs e)
        {
            Button b = (Button)sender;
            if (srcSquare != null)
            {
                // unselected
                if (matBoard[srcSquare.Row, srcSquare.Col] == b)
                {
                 
                    matBoard[srcSquare.Row, srcSquare.Col].FlatAppearance.BorderColor = Color.FromArgb(34, 34, 34);
                    srcSquare = null;
                }
                else
                {
                    dstSquare = (Square)b.Tag;
                    matBoard[dstSquare.Row, dstSquare.Col].FlatAppearance.BorderColor = Color.FromArgb(68, 68, 68);

                    Thread t = new Thread(playMove);
                    t.Start();
                 //   t.IsBackground = true;
                    //playMove();
                }
            }
            else
            {
                srcSquare = (Square)b.Tag;
                matBoard[srcSquare.Row, srcSquare.Col].FlatAppearance.BorderColor = Color.FromArgb(68, 68, 68);
            }
         
        }

        // messages should be according the protocol.
        // index is the message number in the protocol
        string[] messages =  {
            "Valid move",
            "Valid move - you put the opponent in check",
            "Invalid move - not your piece",
            "Invalid move - destination is not free",
            "Invalid move - move would put your king in check",
            "Invalid move - out of bounds",
            "Invalid move - illegal piece movement",
            "Invalid move - source and destination are the same",
            "Game over - checkmate",
            "Game over - stalemate",
            "Game over - draw by insufficient material",
            "Game over - draw by 50-move rule",
            "Game over - draw by threefold repetition",
            };


        string convertEngineToText(string m)
        {
            int res;
            bool b = int.TryParse(m, out res);

            if (!b || res < 0 || res >= messages.Length)
                return messages[messages.Length - 1];

            return messages[res];
        }
        


        void playMove()
        {
            if (isGameOver)
            {
                enginePipe.sendEngineMove("quit");
                enginePipe.close();
            }


            try
            {
                 Invoke((MethodInvoker)delegate {

                     lblEngineCalc.Visible = true;
            
                     lblMove.Text = string.Format("Move from {0} to {1}", srcSquare, dstSquare);
                    lblMove.Visible = true;
                    //lblEngineCalc.Invalidate();
            
                    label2.Visible = false;
                    lblResult.Visible = false;

                    this.Refresh();
            

                    // should send pipe to engine
                    enginePipe.sendEngineMove(srcSquare.ToString() + dstSquare.ToString());
                    

                     // should get pipe from engine
                    string m = enginePipe.getEngineMessage();

                    if (!enginePipe.isConnected())
                    {
                        MessageBox.Show("Connection to engine has lost. Bye bye.");
                        this.Close();
                        return;
                    }

                    string res = convertEngineToText(m);

                    
                     if (res.ToLower().StartsWith("game over"))
                     {
                         isGameOver = true;
                         isCurPlWhite = !isCurPlWhite;
                         lblCurrentPlayer.Text = isCurPlWhite ? "White" : "Black";

                         matBoard[dstSquare.Row, dstSquare.Col].BackgroundImage = matBoard[srcSquare.Row, srcSquare.Col].BackgroundImage;
                         matBoard[srcSquare.Row, srcSquare.Col].BackgroundImage = null;

                         matBoard[srcSquare.Row, srcSquare.Col].FlatAppearance.BorderColor = Color.FromArgb(34, 34, 34);
                         matBoard[dstSquare.Row, dstSquare.Col].FlatAppearance.BorderColor = Color.FromArgb(34, 34, 34);

                     }
                     // added this
                     else if (res.ToLower().StartsWith("valid"))
                     {
                         // get the updated board state
                         string boardState = enginePipe.getEngineMessage();

                         // check if the board state is correct
                         if (boardState.Length == (BOARD_SIZE * BOARD_SIZE + 1))  // + 1 is the player turn
                         {

                             // update the entire board
                             updateBoardDisplay(boardState);

                             isCurPlWhite = !isCurPlWhite;  // swap the player
                             lblCurrentPlayer.Text = isCurPlWhite ? "White" : "Black";
                         }

                         matBoard[srcSquare.Row, srcSquare.Col].FlatAppearance.BorderColor = Color.FromArgb(34, 34, 34);
                         matBoard[dstSquare.Row, dstSquare.Col].FlatAppearance.BorderColor = Color.FromArgb(34, 34, 34);

                     }

                     lblEngineCalc.Visible = false;
                    lblResult.Text = string.Format("{0}", res);
                    lblResult.Visible = true;
                    label2.Visible = true;
                    this.Refresh();
                 });
                
           
                }
                catch
                {

                }
                finally
                {
                    Invoke((MethodInvoker)delegate
                    {
                        if (srcSquare != null)
                            matBoard[srcSquare.Row, srcSquare.Col].FlatAppearance.BorderColor = Color.FromArgb(34, 34, 34);

                        if (dstSquare != null)
                            matBoard[dstSquare.Row, dstSquare.Col].FlatAppearance.BorderColor = Color.FromArgb(34, 34, 34);

                        dstSquare = null;
                        srcSquare = null;

                    });
                }

        }

        //BONUS - added this function
        /*
            fucntion to update the board's display
            input: the board string
            output: no reutrn values
        */
        private void updateBoardDisplay(string boardStr)
        {
            int counter = 0;
            int i = 0, j = 0;

            // swap every square with the new updated one
            for (i = 0; i < BOARD_SIZE; i++)
            {
                for (j = 0; j < BOARD_SIZE; j++)
                {
                    matBoard[i, j].BackgroundImage = getImageBySign(boardStr[counter]);
                    counter++;
                }
            }
        }
        private void Form1_FormClosed(object sender, FormClosedEventArgs e)
        {
            enginePipe.sendEngineMove("quit");
            enginePipe.close();
        }

        private void ApplyTheme()
        {
            const string CHANGE_LIGHT = "Switch To Light Mode";
            const string CHANGE_DARK = "Switch To Dark Mode";
            lblCurrentPlayer.ForeColor = isDarkTheme ? Color.LemonChiffon : Color.Black;
            lblEngineCalc.ForeColor = isDarkTheme ? Color.LemonChiffon : Color.Black;
            lblWaiting.ForeColor = isDarkTheme ? Color.LemonChiffon : Color.Black;
            lblMove.ForeColor = isDarkTheme ? Color.LemonChiffon : Color.Black;
            lblResult.ForeColor = isDarkTheme ? Color.LemonChiffon : Color.Black;
            label1.ForeColor = isDarkTheme ? Color.LemonChiffon : Color.Black;
            label2.ForeColor = isDarkTheme ? Color.LemonChiffon : Color.Black;

            button1.BackColor = isDarkTheme ? Color.FromArgb(18, 18, 18) : Color.White;
            button1.ForeColor = isDarkTheme ? Color.LemonChiffon : Color.Black;
            button1.Text = isDarkTheme ? CHANGE_LIGHT : CHANGE_DARK;

            Color coordColor = isDarkTheme ? Color.LemonChiffon : Color.Black;

            this.BackColor = isDarkTheme ? Color.FromArgb(18, 18, 18) : Color.White;

            foreach (Control c in Controls)
            {
                if (c is Label lbl && (string)lbl.Tag == "BoardCoord")
                {
                    lbl.ForeColor = coordColor;
                    lbl.BackColor = Color.Transparent;
                }
            }
        }


        private void button1_Click(object sender, EventArgs e)
        {
            isDarkTheme = !isDarkTheme;
            ApplyTheme();
        }
    }
}
