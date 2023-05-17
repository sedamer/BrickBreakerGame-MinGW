#include <iostream>
#include <conio.h>
#include <windows.h>

using namespace std;

const int BallSpeed = 2;
const int PaddleSpeed =10;

const int Width = 120;
const int Height = 60;

int ball_x = Width / 2-25; //topun bailang�� pozisyonunu belirleriz
int ball_y = Height - 30;
int ball_dx = -1; //topun hareket y�n�
int ball_dy = -1;

int paddle_x = Width / 2-20; //paddle �n ba�lang�� pozisyonunu belirleriz.
int paddle_y = Height -28;
bool GameStart=false;
bool GameOver = false;
int score = 0;
int lives=3;
const int brick_cols=15; //s�ra say�s�
const int brick_rows=8; //her bir s�radaki tu�la say�s�
bool GameWon = false;

int Bricks[brick_cols][brick_rows] ;

void DrawIntroScreen() //giri� ekran�
{
	if(!GameStart){

	system("cls");

    COORD startTextPosition = { Width / 2-15, Height / 2 -14 };
    COORD exitTextPosition = { Width / 2-15 , Height / 2 -12 };
	COORD TitleTextPosition = { Width / 2 -15, Height / 2 -20 };
	COORD instTextPosition = { Width / 2-15, Height / 2 -10 };
    COORD enjoyTextPosition = { Width / 2-7, Height / 2 -7 };

    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    SetConsoleCursorPosition(hConsole, TitleTextPosition);
    SetConsoleTextAttribute(hConsole, 11);
    cout << "Welcome to Brick Breaker Game!" << endl;

    SetConsoleCursorPosition(hConsole, startTextPosition);
    SetConsoleTextAttribute(hConsole, 14);
    cout << "1.Press Enter key to Start Game" << endl;

    SetConsoleCursorPosition(hConsole,  exitTextPosition);
    cout << "2.Press Esc to Quit Game" << endl;

    SetConsoleCursorPosition(hConsole, instTextPosition);
    SetConsoleTextAttribute(hConsole, 14);
    cout << "3.Press i to read the instructions" << endl;

    SetConsoleCursorPosition(hConsole, enjoyTextPosition);
    SetConsoleTextAttribute(hConsole, 14);
    cout << "ENJOY! :)" << endl;
}
	//Sleep(1000);
}
void Instruction() //i ye bas�ld�g�nda talimatlar b�l�m� ekranda ��kar.
{
//	DrawIntroScreen();
	if(!GameStart){

	system("cls");

    COORD instTextPosition = { Width / 2-23, Height / 2 -14 };
    COORD ilkTextPosition = { Width / 2-28 , Height / 2 -20 };
	COORD ikiTextPosition = { Width / 2 -23, Height / 2 -16 };
    COORD ucTextPosition = { Width / 2-23, Height / 2 -12 };
    COORD backTextPosition = { Width / 2-23, Height / 2 -10 };

    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    SetConsoleCursorPosition(hConsole, ilkTextPosition);
    SetConsoleTextAttribute(hConsole, 11);
    cout << "INSTRUCTION:" << endl;

    SetConsoleCursorPosition(hConsole, instTextPosition);
    SetConsoleTextAttribute(hConsole, 14);
    cout << "2.Use a and d keys to move paddle." << endl;

    SetConsoleCursorPosition(hConsole,  ikiTextPosition);
    cout << "1.Break all the bricks to complete the game." << endl;

    SetConsoleCursorPosition(hConsole, ucTextPosition);
    SetConsoleTextAttribute(hConsole, 14);
    cout <<"3.Press k to back to mainpage" << endl;

    SetConsoleCursorPosition(hConsole, backTextPosition);
    SetConsoleTextAttribute(hConsole, 14);
    cout <<"4.If the ball falls below the paddle, you lose a life. :( " << endl;

	//Sleep(1000);
}
}
void InitGame() //oyun ba��nda tu�lalar�n durumunu tutan fonksiyondur.
{
	// Initialize the bricks
	for (int i = 0; i <brick_cols; i++)
	{
  		for (int j = 0; j < brick_rows; j++)
	{
		Bricks[i][j] = 1;
	}
}
}

void Draw()
{
    system("cls"); // Clear the console screen
    // Draw the bricks
	 for (int i = 0; i < brick_cols; i++) //brickler kontrol edilir�
	    {
	        for (int j = 0; j < brick_rows; j++)
	        {
	            if (Bricks[i][j] > 0)
	            {
                    COORD position = {i * 7 + 3, j * 3 + 2}; //koordinatlar� verilir ve brick �izdirilir
	                HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	                SetConsoleCursorPosition(hConsole, position);
	                SetConsoleTextAttribute(hConsole, 14); // 14 renk kodu: sar�
	                cout << "[####]";
	                SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);

	            }
	        }
    }
    // Draw the paddle
    COORD paddlePosition = { paddle_x, paddle_y };
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleCursorPosition(hConsole, paddlePosition);
    SetConsoleTextAttribute(hConsole, 13); // 13 mor renk kodu

	cout << "=======";

    // Draw the ball
    COORD ballPosition = { ball_x, ball_y };
    SetConsoleCursorPosition(hConsole, ballPosition);
    SetConsoleTextAttribute(hConsole, 9);

    cout << "O";

    // Oyun ba�lad��� zaman ekranda belirtilen konumlarda score , lives ve Brick Breaker Game yaz�s� yazd�r�l�r.
    COORD scorePosition = { 0, Height -28};
    SetConsoleCursorPosition(hConsole, scorePosition);
    SetConsoleTextAttribute(hConsole, 13);
    cout << "score: " << score;
    COORD livesPosition = { Width - 10, Height -28};
    SetConsoleCursorPosition(hConsole, livesPosition);
    SetConsoleTextAttribute(hConsole, 13);
    cout << "lives: " << lives;

    COORD title = { Width /2-20 , Height -57 };
    SetConsoleCursorPosition(hConsole, title);
    SetConsoleTextAttribute(hConsole, 13);
    cout << "BRICK BREAKER GAME ";


}
void CheckGameOver() //oyunun bitip bitmedi�i kntrol�
	{

	if (GameOver) // e�er oyun bitmi�se

	{
		system("cls"); //ekran temizlenir
		//Biti� ekran�na lives , score , ve GAME OVER yaz�s� yazd�r�l�r.
		COORD livessPosition = { Width / 2-15, Height / 2 -12 };
  		COORD gameovaPosition = { Width / 2-15 , Height / 2 -11 };
		COORD scorePosition = { Width/2, Height /2 };
		HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	    SetConsoleCursorPosition(hConsole, scorePosition);
	    SetConsoleCursorPosition(hConsole, livessPosition);
	    SetConsoleCursorPosition(hConsole, gameovaPosition);

		SetConsoleTextAttribute(hConsole, 11);
	    cout << "GAME OVER "<< endl;
		cout << "score: " << score << endl;
		cout << "lives: " << lives << endl;

		exit(0);
	}
}
void collision()
{
	  // topun pozisyonu de�i�tirir.
	    ball_x += ball_dx * BallSpeed;
	    ball_y += ball_dy * BallSpeed;

	    // Check for collisions with the screen edges
	    if (ball_x == 0 || ball_x == Width - 1) //topun sa� ve sol kenarlara �arp�p �arpmad�g� kontrol�
	    {
	        ball_dx = -ball_dx; //topun y�n�ne tersine �evrilir.
	    }
	    if (ball_y == 2) //topun �st s�n�ra �arp���n� kontrol eder.
	    {
	        ball_dy = -ball_dy; //top tersi y�nde hareket eder.
	    }
	    if (ball_y >= Height - 1) // top zemine �arparsa;
	    {
	        lives--; //can 1 azalacak.
	        if (lives <= 0) // e�er oyuncunun can� 0 olursa ;
	        {
	            GameOver = true; //oyun bitecek.
	        }
	        else // di�er t�rl� de ball ve paddle konumlar� ba�lang��taki gibi olacak.
	        {
	             ball_x = Width / 2-25;
				 ball_y = Height - 33;
				 ball_dx = -1;
				 ball_dy = -1;

				 paddle_x = Width / 2-20;
				 paddle_y = Height -28;
	             GameStart = false;
	        }
	    }
	     // If the ball is within the screen

	        // top paddle a �arpt�g� zaman y�n de�i�ecek ve yukar� hareket edecek.
	    if (ball_y == paddle_y + 1 && ball_x >= paddle_x && ball_x < paddle_x + 7) {
      	  ball_dy = -ball_dy;
    }

	        // Check for collisions with the bricks

	    /*int brick_x = ball_x / 7;
	    int brick_y = (ball_y - 2) / 3;
	    if (brick_y >= 0 && brick_y < brick_rows && Bricks[brick_x][brick_y] > 0)
	        {
	           Bricks[brick_x][brick_y] = 0; // Destroy the brick
	           score += 10; // Increase the score
	           ball_dy = -ball_dy; // Reverse the ball's direction
	        }
	    	    Sleep(1000);
 */

	  for (int i = 0; i < brick_cols; i++)
    {
        for (int j = 0; j < brick_rows; j++) //brickleri tek tek gezecek ve e�er k�r�lmayan varsa;

        {
            if (Bricks[i][j] > 0)
            {
                int brick_x = i * 7 + 3;
                int brick_y = j * 3 + 2;
				//topun tu�laya �arp�p �arpmad��� kontrol� yap�lacak
                if (ball_x >= brick_x && ball_x < brick_x + 6 && ball_y >= brick_y && ball_y < brick_y + 3)
                {
                	//e�er �arparsa tu�la k�r�lacak ve score a 100 puan eklenecek.
                    Bricks[i][j]--;
                    score+=100;
                  /*  if (score == brick_cols * brick_rows)
                    {
                        GameOver = true;
                    }
*/
                   //tu�la vuruldu�unda topun hangi taraftan �arpt���na ba�l� olarak topun y�n�n� tersine �evirecek.

                    if (ball_x == brick_x || ball_x == brick_x + 6) // sa� ve sol konrol�
                    {
                        ball_dx = -ball_dx;
                    }
                    else
                    {
                        ball_dy = -ball_dy;
                    }
                }
            }
        }

    }
     //Sleep(500);
// Check if the game is won
//
//t�m tu�lalar�n yok edilip edilmedi�ini kontrol i�in t�m bricler for ile taran�r.
	for (int i = 0; i < brick_cols; i++)
	{
		for (int j = 0; j < brick_rows; j++)
		{
			if (Bricks[i][j] > 0) // e�er hala brick varsa Gamewon false olur yani oyun devam eder.
			{
				GameWon = false;
			}
		}
	}

	if (GameWon) //e�er t�m tu�lalar biterse;
	{
		GameOver = true; //oyun sonlan�r.
		system("cls");
		//score,lives ve cong. yaz�s� yazd�r�l�r.
		COORD scorePosition = { Width / 2, Height / 2 };
		HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleCursorPosition(hConsole, scorePosition);
		SetConsoleTextAttribute(hConsole, 10);
		cout << "CONGRATULATIONS!" << endl;
		cout << "You have won the game!" << endl;
		cout << "score: " << score << endl;
		cout << "lives: " << lives << endl;

		exit(0);
}
}
  

void MovePaddle(){
	if (_kbhit()) { // check if key is pressed
    int key = _getch();

	    if (key == 27) { // Esc bas�l�rsa oyun kapat�l�r.
	        GameOver = true;
	        CheckGameOver();

	  		}
		else if (key == 13) { // enter'a bas�l�rsa oyun ba�lar. //!GameStart &&
		        GameStart = true;
		        InitGame();

		    }
		else if(key ==105  ) { // i ye bas�l�rsa instruction b�l�m� a��l�r.
			GameStart = false;
			GameOver = false;
	    	Instruction();

			}
		else if(key ==107 ){ //k ya bas�l�rsa giri� ekran�na geri d�ner.
			GameStart = false;
			GameOver = false;
	    	DrawIntroScreen();

			}
	    else if (key == 97) // a ya basl�rsa paddle sola so�ru hareket eder
	        {
	            paddle_x -= PaddleSpeed;
	            if (paddle_x < 0) paddle_x = 0;
	        }
	    else if (key == 100) // d ye bas�l�rsa paddle sa�a do�ru hareket eder.
	        {
	            paddle_x += PaddleSpeed;
	            if (paddle_x > Width - 7) paddle_x = Width - 7;
			}

	}
}

	// Update the game state
void Update(){
		collision();
		MovePaddle();
		Draw();
		CheckGameOver();
}

int main()
	{


	DrawIntroScreen();
	MovePaddle();
	//Instruction();
	//InitGame();
	while(GameStart==false){
            MovePaddle();
        if(GameStart==true){
            break;
        }
	}
	while (!GameOver) //lives > 0 &&
	{
	    // Update the game state
		 	Update();
	        Sleep(500);
	}

	return 0;
}

