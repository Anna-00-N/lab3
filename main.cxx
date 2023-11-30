#include <iostream> //ввод-вывод
#include <string>
#include <fstream>
#include <sstream>
#include <math.h>

using namespace std; //стандартная среда имён

class Func{
	private:
		double x;
		double y;
		double line(double k, double m, double x, double x_sdvig=0, double y_sdvig=0)
		{
			return (k*(x-x_sdvig)+m+y_sdvig);
		}
		double circle(int flag, double R, double x, double x_sdvig=0, double y_sdvig=0)
		{
			int half = (flag==0)?(1):(-1);
			double sqrR = R*R-(x-x_sdvig)*(x-x_sdvig);
			return (sqrR<0)?(NAN):(half*sqrt(sqrR)+y_sdvig);
		}
	public:
		void count_y(){
			if(x<=-3){
				y = line(1, 3, x);
			}
			else if(x<=0){
				y = circle(0, 3, x);
			}
			else if(x<=6){
				y = line(-0.5, 0, x, 0, 3);
			}
			else{
				y = line(1, 0, x, 6, 0);
			}	
		}
		Func(){ x = 0; y = 0; }
		Func operator=(double x0){ x = x0; count_y(); return *this; }
		Func operator=(int x0){ x = 1.0*x0; count_y(); return *this; }
		void set_x(double x0){ x = x0;count_y(); }
		void set_x(int x0){ x = 1.0*x0;count_y(); }
		double get_y(){ count_y(); return y;}
		friend ostream &operator<<(ostream &os, Func &f){ return os<<f.x<<" "<<f.y; }
		friend istream &operator>>(istream &in, Func &f){ 
			in>>f.x>>f.y;
			return in; }
};

class My{
	private:
		Func *f;
		string f_name;
		int n;

	public:
		My(double L, double H, double d){ //L - наименьшее значение, H - наибольшее значение, d - шаг
			double i = L; 
			n=0; 
			while(H>=(L+n*d)) n++; 
			f = new Func[n];
			for(int i=0; i<n; i++) f[i]=L+i*d;
		}
		void set_file(string f){ f_name = f; }
		void write(){
			ofstream F1(f_name);
			for(int i=0; i<n; i++)  F1<<f[i]<<endl;
			F1.close();
		}
		void read(){
			Func f;
			ifstream F2(f_name); string s;
			while(!F2.eof()){
				stringstream s1;
				getline(F2,s);
				if(s.size()>0){
					s1<<s; 
					s1>>f;
					cout<<f<<endl;
				}
			}
			F2.close(); //закрыть файл, открытый для чтения
		}
		~My(){ delete [] f; }

};

int main(int argc, char *argv[])
{
	My A(-10,10,0.5);
	A.set_file("my.txt");
	A.write();
	A.read();
	cin.get(); //ожидание ввода символа
	return 0;
}