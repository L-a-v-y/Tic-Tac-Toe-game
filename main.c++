#include <iostream>
using namespace std;
#define side 3

class ticTacToe{
    char board[side][side];
    char computer='x';
    char human='o';
    char empty='*';
    public:
    ticTacToe(){
        for(int i=0; i<side; i++){
            for(int j=0; j<side; j++){
                board[i][j]=empty;
            }
        }
    }
    void showBoard(){
        for(int i=0; i<side-1; i++){
            cout<<"  ";
            for(int j=0; j<side-1; j++){
                cout<<board[i][j]<<" | ";
            }
            cout<<board[i][side-1];
            cout<<endl;
            cout<<" ";
            for(int j=0;j<side-1;j++){
                cout<<"----";
            }
            cout<<"---";
            cout<<endl;
        }
        cout<<"  ";
        for(int j=0; j<side-1; j++){
            cout<<board[side-1][j]<<" | ";
        }
        cout<<board[side-1][side-1];
        cout<<endl<<endl;
    }
    void showCoordinates(){

    }
    bool movesLeft(){
        for(int i=0;i<3;i++){
            for(int j=0;j<3;j++){
                if(board[i][j]==empty){
                    return true;
                }
            }
        }
        return false;
    }
    bool isFeasible(int x, int y){
        if(board[x][y]==empty){
            return true;
        }
        return false;
    }
    int gameOver(){
        for(int i=0;i<3;i++){
            if(board[i][0]==board[i][1] && board[i][1]==board[i][2]){
                if(board[i][0]==computer){
                    return 10;
                }
                else if(board[i][0]==human){
		            return -10;
		        }
            }
        }
        for(int j=0;j<3;j++){
            if(board[0][j]==board[1][j] && board[1][j]==board[2][j]){
                if(board[0][j]==computer){
                    return 10;
                }
		        else if(board[0][j]==human){
		            return -10;
		        }
            }
        }
        if(board[0][0]==board[1][1] && board[1][1]==board[2][2]){
            if(board[0][0]==computer){
                return 10;
            }
            else if(board[0][0]==human){
		        return -10;
	        }
        }
        if(board[0][2]==board[1][1] && board[1][1]==board[2][0]){
            if(board[0][2]==computer){
                return 10;
            }
            else if(board[0][2]==human){
		        return -10;
	        }
        }
        return 0;
    }
    int calculateRating(bool humanTurn){
        int g=gameOver();
        if(g==10 || g==-10){
            return g;
        }
        if(!movesLeft()){
            return 0;
        }
        int res;
        if(humanTurn){
            res=100;
            for(int i=0;i<3;i++){
                for(int j=0;j<3;j++){
                    if(board[i][j]==empty){
                        board[i][j]=human;
                        res=min(res, calculateRating(!humanTurn));
                        board[i][j]=empty;
                    }
                }
            }
        }
        else{
            res=-100;
            for(int i=0;i<3;i++){
                for(int j=0;j<3;j++){
                    if(board[i][j]==empty){
                        board[i][j]=computer;
                        res=max(res, calculateRating(!humanTurn));
                        board[i][j]=empty;
                    }
                }
            }
        }
        return res;
    }
    void optimalMove(){
        int  max_rating=-100;
        int x=32, y=32;
        for(int i=0;i<3;i++){
            for(int j=0;j<3;j++){
                if(board[i][j]==empty){
                    board[i][j]=computer;
                    // cout<<i<<' '<<j<<endl;
                    int rating=calculateRating(true);
                    // cout<<"score: "<<score<<endl;
                    board[i][j]=empty;
                    if(rating>max_rating){
                        max_rating=rating;
                        x=i; y=j;
                    }
                }
            }
        }
        board[x][y]=computer;
    }
    void playGame(bool humanTurn){
        int isOver=0;
        bool emptySpace=true;
        while(isOver==0 && emptySpace){
            if(humanTurn==true){
                showBoard();
                int x, y;
                cout<<"Enter the place you want to mark: "<<endl;
                cin>>x>>y;
                if(isFeasible(x+1, y+1)){
                    board[x+1][y+1]=human;
                    humanTurn =false;
                }
                else{
                    cout<<"The entered place is invalid. Enter an empty place: "<<endl;
                }
            }
            else{
                showBoard();
                optimalMove();
                humanTurn=true;
            }  
            isOver=gameOver();
            emptySpace=movesLeft();
        }
        if(isOver==10){
            showBoard();
            cout<<"You lost! Time to try again!"<<endl;
        }
        else if(isOver==-10){
            showBoard();
            cout<<"YaY, You Win!! Try beating me again!"<<endl;
        }
        else{
            showBoard();
            cout<<"It's a tie! It was really tough for me! Think you can beat me next time?"<<endl;
        }  
    }
};
int main(){
    char play='Y';
    bool humanTurn;
    char firstTurn;
    cout<<"If you would want to play first press Y."<<endl;
    cin>>firstTurn;
    if(firstTurn=='Y'){
        humanTurn=true;
    }
    else{
        humanTurn =false;
    }
    while(play=='Y'){
        ticTacToe game;
        game.playGame(humanTurn);
        cout<<"Press Y to play again, N to leave the game."<<endl;
        cin>>play;
    }
}