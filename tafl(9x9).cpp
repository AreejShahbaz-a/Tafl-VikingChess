#include<iostream>
#include<fstream>
using namespace std;
enum player{attacker, defender};
class Pieces{
	public:
		char board[9][9];
		bool illegalmove(int new_row, int new_col, int row, int col)
		{
			if(new_row>8||new_row<0||new_col>8||new_col<0)
			{
				return true;
			}
			if(board[new_row][new_col]!=' ')
			{
				return true;
			}
			if(board[row][col]!='k')
			{
				if((new_row==0&&new_col==0)||(new_row==0&&new_col==8)||(new_row==8&&new_col==0)||(new_row==8&&new_col==8))
				{
					return true;
				}
				if(new_row==4&&new_col==4)
				{
					return true;
				}
			}
			if(new_row!=row && new_col!=col)
			{
				return true;
			}
			if(board[row][col]=='d')
			{
				if((board[new_row-1][new_col]=='a'||((new_row-1)==4&&new_col==4))&&
					(board[new_row+1][new_col]=='a'||((new_row+1)==4&&new_col==4)))
				{
					return true;
				}
				if((board[new_row][new_col-1]=='a'||((new_col-1)==4&&new_row==4))&&
					(board[new_row][new_col+1]=='a'||((new_col+1)==4&&new_row==4)))
				{
					return true;
				}
			}
			if(board[row][col]=='a')
			{
				if((board[new_row-1][new_col]=='d'||board[new_row-1][new_col]=='k'||((new_row-1)==4&&new_col==4))&&
					(board[new_row+1][new_col]=='d'||board[new_row+1][new_col]=='k'||((new_row+1)==4&&new_col==4)))
				{
					return true;
				}
				if((board[new_row][new_col-1]=='d'||board[new_row][new_col-1]=='k'||((new_col-1)==4&&new_row==4))&&
					(board[new_row][new_col+1]=='d'||board[new_row][new_col+1]=='k'||((new_col+1)==4&&new_row==4)))
				{
					return true;
				}
			}
			return false;
		}
		void destination(int row, int col)
		{
			destination_again:
			int des_row, des_col;
			cout<<"Which row do you want to move too";
			cin>>des_row;
			des_row--;
			cout<<"Which col do you want to move too";
			cin>>des_col;
			des_col--;
			while(illegalmove(des_row,des_col,row,col))
			{
				cout<<"Illegal move\nTry again\n";
				goto destination_again;
			}
			board[des_row][des_col]=board[row][col];
			board[row][col]=' ';
		}
		void capture_piece(int *win)
		{
			for(int i=0;i<9;i++)
			{
				for(int j=0;j<9;j++)
				{
					if(board[i][j]=='d')
					{
						if((board[i-1][j]=='a'||((i-1)==4&&j==4))&&
							(board[i+1][j]=='a'||((i+1)==4&&j==4)))
						{
							board[i][j]=' ';
						}
						if((board[i][j-1]=='a'||((j-1)==4&&i==4))&&
							(board[i][j+1]=='a'||((j+1)==4&&i==4)))
						{
							board[i][j]=' ';
						}
					}
					if(board[i][j]=='a')
					{
						if((board[i-1][j]=='d'||board[i-1][j]=='k'||((i-1)==4&&j==4))&&
							(board[i+1][j]=='d'||board[i+1][j]=='k'||((i+1)==4&&j==4)))
						{
							board[i][j]=' ';
						}
						if((board[i][j-1]=='d'||board[i][j-1]=='k'||((j-1)==4&&i==4))&&
						(board[i][j+1]=='d'||board[i][j+1]=='k'||((j+1)==4&&i==4)))
						{
							board[i][j]=' ';
						}
					}
					if(board[i][j]=='k')
					{
						if(board[i-1][j]=='a'&&board[i+1][j]=='a'&&board[i][j-1]=='a'&&board[i][j+1]=='a')
						{
							*win=1;
						}
						if(board[i-1][j]=='a'&&board[i+1][j]=='a'&&board[i][j-1]=='a'&&(j==8||((j+1)==4&&i==4)))
						{
							*win=1;
						}
						if(board[i-1][j]=='a'&&board[i+1][j]=='a'&&board[i][j+1]=='a'&&(j==0||((j-1)==4&&i==4)))
						{
							*win=1;
						}
						if(board[i-1][j]=='a'&&board[i][j+1]=='a'&&board[i][j-1]=='a'&&(i==8||((i+1)==4&&j==4)))
						{
							*win=1;
						}
						if(board[i+1][j]=='a'&&board[i][j+1]=='a'&&board[i][j-1]=='a'&&(i==0||((i-1)==4&&j==4)))
						{
							*win=1;
						}
						if(i==8)
						{
							if((board[i][j-1]=='a'||j==0)&&board[i+1][j]=='a'&&(board[i][j+1]=='a'||j==8))
							{
								*win=1;
							}
						}
						if(i==0)
						{
							if((board[i][j-1]=='a'||j==0)&&board[i-1][j]=='a'&&(board[i][j+1]=='a'||j==8))
							{
								*win=1;
							}
						}
						if(j==8)
						{
							if((board[i-1][j]=='a'||i==0)&&board[i][j+1]=='a'&&(board[i+1][j]=='a'||i==8))
							{
								*win=1;
							}
						}
						if(j==0)
						{
							if((board[i-1][j]=='a'||i==0)&&board[i][j-1]=='a'&&(board[i+1][j]=='a'||i==8))
							{
								*win=1;
							}
						}
					}
				}
			}
		}
		bool winningmovedefender()
		{
			if(board[0][0]=='k'||board[0][8]=='k'||board[8][0]=='k'||board[8][8]=='k')
			{
				return true;
			}
			return false;
		}
};
class gameboard: public Pieces{
	public:
		string line;
		player currentplayer=attacker;
		void showplayer()
		{
			if(currentplayer==attacker)
			{
				cout<<"It is the attacker's Turn";
			}
			else
			{
				cout<<"It is the defender's Turn";
			}
		}
		void changeplayer()
		{
			if(currentplayer==attacker)
			{
				currentplayer=defender;
			}
			else
			{
				currentplayer=attacker;
			}
		}
		void firstboard()
		{
		ifstream file("taflboard.txt");
		if(file.is_open())
		{
		for(int i=0;i<9;i++)
		{
			getline(file,line);
			for(int j=0;j<9;j++)
			{
			if(line[j]!='.')
			{
				board[i][j]=line[j];
			}
			else
			{
				board[i][j]=' ';
			}		
			}
		}
		}
	}
		void printboard()
		{
		for(int i=0;i<9;i++)
		{
			cout<<"    "<<i+1;
		}
		cout<<endl;
	    for(int i=0;i<9;i++)
		{
			cout<<i+1;
			cout<<" | ";
			for(int j=0;j<9;j++)
			{
			cout<<board[i][j]<<" ";	
			cout<<" | ";
			}
			cout<<endl;
		}
		}
		void move_piece()
		{
			int row, col;
			makemoveagain:
			row_again:
			cout<<"\nEnter row of the piece you want to change";
			cin>>row;
			if(row>9||row<1)
			{
				cout<<"Invalid Row\nTry again\n";
				goto row_again;
			}
			row--;
			col_again:
			cout<<"Enter column of the piece you want to change";
			cin>>col;
			if(col>9||col<1)
			{
				cout<<"Invalid Column\nTry again\n";
				goto col_again;
			}
			col--;
			if(board[row][col]==' ')
			{
				cout<<"This is a blank space\n choose a piece";
				goto makemoveagain;
			}
			else if(board[row][col]=='a')
			{
				cout<<"This is a attack piece"<<endl;;
				if(currentplayer!=attacker)
				{
					cout<<"You are not allowed to move this piece";
					goto makemoveagain;
				}
					destination(row,col);
			}
			else if(board[row][col]=='d')
			{
				cout<<"This is a defense piece"<<endl;
				if(currentplayer!=defender)
				{
					cout<<"You are not allowed to move this piece";
					goto makemoveagain;
				}
				destination(row,col);
			}
			else if(board[row][col]=='k')
			{
				cout<<"This is a king piece"<<endl;
				if(currentplayer!=defender)
				{
					cout<<"You are not allowed to move this piece";
					goto makemoveagain;
				}
				destination(row,col);
			}
		}
			
};
int main()
{
	char choice;
	play_again:
	int win=0;
	gameboard g1;
	system("cls");
	g1.firstboard();
	while(true)
	{
		g1.printboard();
		g1.showplayer();
		g1.move_piece();
		g1.capture_piece(&win);
		if(win==1)
		{
			system("cls");
			cout<<"THE ATTACKER WINS!"<<endl;
			goto gameend;
		}
		if(g1.winningmovedefender())
		{
			system("cls");
			cout<<"THE DEFENDER WINS!"<<endl;
			goto gameend;
		}
		g1.changeplayer();
		system("cls");
	}
	gameend:
		g1.printboard();
		cout<<"Press Y/y to play again";
		cin>>choice;
		if(choice=='Y'||choice=='y')
		{
			goto play_again;
		}
		else
		{
			return 0;
		}
}
