
#include<iostream>  
#include<fstream>    
#include<string>  

using namespace std;

void д��TXT(string ����, string ����, bool �Ƿ񸲸�) {
	ofstream д��(����, �Ƿ񸲸� ? ios::trunc : ios::app);

	if (д��.is_open()) {//����ɹ��Ļ�       
		д�� << ���� << endl;
		д��.close();
	}
}
int main() {
	fstream ���ļ�;
	string Ŀ¼ = "C:\\Users\\zhumingde\\Desktop\\�ɼ�\\thumb\\";
	���ļ�.open(Ŀ¼+"Rect.txt");
	string s; int a=220, b=140, c=200, d=200;
//	���ļ� >> s;
//	���ļ� >> a >> b >> c >> d;
	д��TXT(Ŀ¼+"train.xml", "<dataset>", 0);
	д��TXT(Ŀ¼+"train.xml", "<images>", 0);
//	string temp = "<image file='"+s+"'>";
//	д��TXT(Ŀ¼+"\\train.xml", temp, 0);
//	temp = "<box top='" + to_string(a)+"' left='"+to_string(b)+"' width='"+to_string(c)+"' height='"+to_string(d)+"'/>";
//	д��TXT(Ŀ¼+"\\train.xml", temp, 0);
	while (!���ļ�.eof()) {
		���ļ� >> s;
		���ļ� >> a >> b >> c >> d;
		cout << "������..." << endl;
	//	д��TXT(Ŀ¼+"\\train.xml", "<image>", 0);
		string temp = "<image file='" + s + "'>";
		д��TXT(Ŀ¼+"train.xml", temp, 0);
		temp = "<box top='" + to_string(b) + "' left='" + to_string(a) + "' width='" + to_string(c) + "' height='" + to_string(d) + "'/>";
		д��TXT(Ŀ¼+"train.xml", temp, 0);
		д��TXT(Ŀ¼+"train.xml", "</image>", 0);
	}
	д��TXT(Ŀ¼+"train.xml", "</images>", 0);
	д��TXT(Ŀ¼+"train.xml", "</dataset>", 0);
	system("pause");
}