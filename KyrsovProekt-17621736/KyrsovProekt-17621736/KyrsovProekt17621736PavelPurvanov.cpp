#include <iostream>
#include <string>
#include <time.h>
#include <fstream>
#include <vector>
#include <list>
#include <algorithm>
#include <map>
using namespace std;

//���� �� ���������
enum EnumG
{
	fantasy = -1,
	action = 0,
	drama = 1,
	triler = 2,
	comedy = 3
};

class CFilms
{
private:
	string MTitle;//�������� �� �����
	string MProducer;//���������
	int MEdition;//�����
	int MYear;//������ �� ��������
	EnumG MGenre;//����

public:

	//default constructor
	CFilms()
	{}

	//explicic constructor
	CFilms(string& mTitle, string& mProducer, int mEdition, int mYear, const EnumG& mGenre)
		:MTitle(mTitle)
		, MProducer(mProducer)
		, MEdition(mEdition)
		, MYear(mYear)
		, MGenre(mGenre)
	{
	}

	//copy constructor
	CFilms(const CFilms& cFilms)
	{
		MTitle = cFilms.MTitle;
		MProducer = cFilms.MProducer;
		MEdition = cFilms.MEdition;
		MYear = cFilms.MYear;
		MGenre = cFilms.MGenre;
	}

	//set
	void SetMovieTitle(const string& mTitle) { MTitle = mTitle; }
	void SetMovieProducer(const string& mProducer) { MProducer = mProducer; }
	void SetEdition(int mEdition) { MEdition = mEdition; }
	void SetYear(int mYear) { MYear = mYear; }
	void SetGenre(const EnumG& mGenre) { MGenre = mGenre; }

	//get
	int GetEdition()
	{return MEdition;}
	EnumG GetGenre()
	{return MGenre;}
	string GetProducer()
	{return MProducer;}
	int GetYear()
	{return MYear;}

	//print to console
	void PrintConsole(ostream& out)
	{Print<ostream>(out);}
	//print to file
	void PrintFile(ofstream& in)
	{Print<ofstream>(in);}

	//1.������������ �� �����
	bool ValidationGenre()
	{return !GetGenre(MGenre).empty();}

	//2.��������� ��������� �� �����/���������� �-� GetCurrentYear
	int GetMAge()
	{return GetCurrentYear() - MYear;}

	//3.��������� ������� �� ����� �� �������
	void Printer(const string& FName)
	{
		ofstream file(FName);
		PrintFile(file);
		file.close();
	}

	//4.�������� �� �����������
	CFilms& operator = (const CFilms& obj)
	{
		this->MTitle = obj.MTitle;
		this->MProducer = obj.MProducer;
		this->MEdition = obj.MEdition;
		this->MYear = obj.MYear;
		this->MGenre = obj.MGenre;

		return *this;
	}

	//5.��������� ��������, ���������� ���� ������ � �������� ���� �������� ������
	bool operator == (const CFilms& obj)
	{
		return obj.MYear == GetCurrentYear();
	}

	//6.�������� �� ��������� > (�� �����(Edition))
	friend bool operator >(const CFilms& obj, const CFilms& jbo)
	{
		return obj.MEdition == jbo.MEdition;
	}

	//7.�������� �� ���������� (�� ���������(Producer))
	friend bool operator == (const CFilms& obj, const CFilms& jbo)
	{
		return obj.MProducer == jbo.MProducer;
	}

protected:

	//�������� ���������, ����� ��� ������� ����(����), ����� ����� ��� ������� �� ������
	static string GetGenre(const EnumG& EnumG)
	{
		switch (EnumG)
		{
		case EnumG::fantasy:
			return "fantasy";
		case EnumG::action:
			return "action";
		case EnumG::drama:
			return "drama";
		case EnumG::triler:
			return "triler";
		case EnumG::comedy:
			return "comedy";

		default:
			return "";
		}
	}

	//�������� ���������, ����� �� ������ �� ��������� �� ������� � ����
	template<typename T>
	void Print(T& stream)
	{
		stream << "\n�������� �� �����: " << MTitle
			<< " ���������: " << MProducer
			<< " �����: " << MEdition
			<< " ������ �� ��������: " << MYear
			<< " ����: " << GetGenre(MGenre) << endl;
	}

	//������� ����� ����� �������� ������, ���������� �� ����������� �� 2.��������� ��������� �� �����
	int GetCurrentYear()const
	{
		time_t Time = time(NULL);
		tm *aTime = localtime(&Time);

		int nCurrentYear = aTime->tm_year + 1900;

		return nCurrentYear;
	}
};

//���� ���������������
class CRazprostranitel
{
private:
	CFilms MFilms;//�����
	string MRazprostranitel;//��� �� ����������������
	int MCount;//���� ��������� �����
	double MIncomes;//������� �� ������

public:
	//default constructor
	CRazprostranitel(){}

	//explicic constructor
	CRazprostranitel(CFilms& mFilms,string& mRazprostranitel, int mCount, double mIncomes)
		:MFilms(mFilms)
		, MRazprostranitel(mRazprostranitel)
		, MCount(mCount)
		, MIncomes(mIncomes)
	{
	}

	//copy constructor/1.��������� �� ����� ���� ���� �����.
	CRazprostranitel(const CRazprostranitel& object)
	{
		MFilms = object.MFilms;
		MRazprostranitel = object.MRazprostranitel;
		MCount = object.MCount;
		MIncomes = object.MIncomes;
	}
	
	//2.�������, ���������� ���� ������ � ��������� ������ �� ������.
	bool IsMovieSoldOnce()
	{return MIncomes > 0;}

	//get
	CFilms GetFilms()const
	{
		return MFilms;
	}

	string GetRName()const
	{
		return MRazprostranitel;
	}

	int GetMoviesCount()const
	{
		return MCount;
	}

	double GetIncome()const
	{
		return MIncomes;
	}

	//�������� �� ��������� � �����
	friend ostream & operator <<(ostream& out, const CRazprostranitel& jbo)
	{
		out << "\n��� �� ���������������: " << jbo.MRazprostranitel
			<< " ���� �����: " << jbo.MCount
			<< " ������� �� ���� ������: " << jbo.MIncomes;

		jbo.GetFilms().PrintConsole(out);

		return out;
	}

};

// �� �� �������� �������� �� "vector<CRazprostranitel>", ������ �� � ����������.
typedef vector<CRazprostranitel> vCRazprostranitel;

//�������� ���������, �� �������� �� �������� � �����.
//���������� �� ������������� �� 1.��������� �� ������� � ����� �� 50 000 ����� �� ���� �������.
template<typename func>
void ElementsToList(const vCRazprostranitel& vCRazprostranitel, list<CFilms>& lFilms, func condition)
{
	vCRazprostranitel::const_iterator iter = vCRazprostranitel.begin();

	while ((iter = find_if(iter, vCRazprostranitel.end(), condition)) != vCRazprostranitel.end())
	{
		lFilms.push_back(iter->GetFilms());

		++iter;
	}
	cout<<"������ ���� ��������."<<endl;
}

//�������, ����� ����� ������� � ����� �� ����� (strFileName), ����� false, ��� ��� ������� � �����
bool GetFromFile(const string& strFileName, vCRazprostranitel& vCRazprostranitel)
{
	ifstream file;

	file.open(strFileName);

	if (!file.is_open())
		return false;

	string strMovieTitle, strMovieProducer, strDistributorName;
	int nDrawing = 0, nYear = 0, nGenre = 0, nMoviesCount = 0;
	double dIncomeForOneYear;

	//������ �� ������� �� �����, ��� �� ���
	while (file >> strMovieProducer >> strMovieTitle >> nDrawing >> nYear >> nGenre >> strDistributorName >> nMoviesCount >> dIncomeForOneYear)
	{
		//��������� �� ����� �����
		CFilms oFilms(strMovieTitle, strMovieProducer, nDrawing, nYear, (EnumG)nGenre);

		//�������� ��� �������
		vCRazprostranitel.emplace_back(CRazprostranitel(oFilms, strDistributorName, nMoviesCount, dIncomeForOneYear));
	}
	
	//��������� �� �����
	file.close();

	
	return true;
}

//2. �� �� ������� � ������� ������� ������ ����������������, ����� ��������������� 
//����� �� ���� � ���� ����������
void GetCommonProducers(const vCRazprostranitel& vCRazprostranitel)
{
	//����� �� ����� ����� �� �� �������� ����� ������: File1,2,3,4,5 � �.�.
	string strFileName = "File";
	int nCounter = 1;

	//��������� map �� ���������� �� ������ ����-�������� -> ���������-������ ��� ������������
	map<string, vector<string>> mProducerKeys;

	//������� �� �������
	for (auto it = vCRazprostranitel.begin(); it != vCRazprostranitel.end(); ++it)
	{
		mProducerKeys[it->GetFilms().GetProducer()].emplace_back(it->GetRName());
	}

	//���������� �� �� ���� �� ���������� (���������) �� ��������� ���������
	//� �������� ���-� ������ ������� �� ������� � ��-����� ��� ����� �� 2, ������ ���� ������ �� �������� ������� ������
	for (auto it = mProducerKeys.begin(); it->second.size() >= 2; ++it)
	{
		ofstream file(strFileName + to_string(nCounter++) + ".txt");

		file << "���������: " << it->first << endl;

		for (auto vIt = it->second.begin(); vIt != it->second.end(); ++vIt)
		{
			file << "���������������: " << *vIt << endl;
		}

		file.close();
	}
	cout<<"��������� ���� ���������."<<endl;
}

//3.�� �� ������� ���������� �� �������, ����� �� ��� 20 �� ���������,
//����� ��� � �������� ���� ���������.
void PrintMoviesByProducerName(const vCRazprostranitel& vCRazprostranitel, const string& strProducerName)
{
	const int MOVIES_COUNT = 20;
	vCRazprostranitel::const_iterator iter = vCRazprostranitel.begin();

	//������ ��� �������� ��� �������, ����� ��������� �� ���������
	//���������� �� ������ �����(�������� �������)
	while ((iter = find_if(iter, vCRazprostranitel.end(), [&strProducerName, &MOVIES_COUNT](const CRazprostranitel& obj)
	{
		return obj.GetFilms().GetProducer() == strProducerName && obj.GetMoviesCount() > MOVIES_COUNT;

	})) != vCRazprostranitel.end())
	{
		//��� ��� ������� �������, �������� �������
		iter->GetFilms().PrintConsole(cout);

		//������������� ���������
		//������� �������������, �� �� �� ������� �������� �� ������������ �� CRazprostranitel ��� ����� �������������
		++iter;
	}
}

//4.�� �� ������� ������ ����� �� ������������������ � ���� �������,
//�������� ���� ��������� �� ������� ����.
bool GetDistributorsByIncomes(const vCRazprostranitel& vCRazprostranitel, const string& strFileName)
{
	//�������� �� �����
	ifstream file;

	file.open(strFileName);

	if (!file.is_open())
		return false;

	double dIncome;

	//������ �� ���������� �� ������� �� ����� �� �������� ��������
	file >> dIncome;

	file.close();

	//�������� �� �������� �� �������
	vCRazprostranitel::const_iterator iter = vCRazprostranitel.begin();

	//������ ����� �������, � ������ ���� � ������� �������
	while ((iter = find_if(iter, vCRazprostranitel.end(), [&dIncome](const CRazprostranitel& obj)
	{
		return obj.GetIncome() == dIncome;

	})) != vCRazprostranitel.end())
	{
		cout << *iter;

		++iter;
	}
}

//5.��� ������� ��������� ������ �� ������������, �� �� ������� ������������������ ��
//������ �����, ����� �� �� ���� ����� ��� �����.
void GetDistributorsByYear(const vCRazprostranitel& vCRazprostranitel, int nYear)
{
	//������ ������ ����� �� �������� �� ������� ������ �� ������ � ����
	vCRazprostranitel::const_iterator iter = vCRazprostranitel.begin();

	while ((iter = find_if(iter, vCRazprostranitel.end(), [&nYear](const CRazprostranitel& obj)
	{
		return obj.GetFilms().GetYear() == nYear
			&& (obj.GetFilms().GetGenre() == EnumG::action || obj.GetFilms().GetGenre() == EnumG::drama);

	})) != vCRazprostranitel.end())
	{
		//��������� �� ����� �� ������������
		cout << "\n���������������: " << iter->GetRName();

		++iter;
	}
}


int main()
{
	setlocale(LC_ALL, "Bulgarian");

	//��������� �� ������ �� ������
	vCRazprostranitel vCRazprostranitel;

	//��������� �� ������ �� �����
	list<CFilms>lFilms;

	//��������� �� ����� �� 10 ��������, �� �� �� �������� ������� �������� �� �����
	//������ .reserve �� �� �������� ������, ������ ����� ����� �� ���� �������� �� �������� � ����������
	vCRazprostranitel.reserve(10);

	//����� �� �����,���� ������� (GetFromFile), �� �� �������� ������ �� ����� �� "����"
	if (!GetFromFile("movies.txt", vCRazprostranitel))
		return _CRT_ERROR;

	char choice, choice2;
	int izbor;
	do {
		do {//������ ����
			cout<<"1.��������� � list ������� � ����� ��� 50000 ����� �� ���� �������: "<<endl;
			cout<<"2.��������� � ������� ������� ������ ����������������, ����� ��������������� ����� �� ���� � ���� ����������: "<<endl;
			cout<<"3.���������� �� �������, ����� �� ��� 20 �� ���������(������� ���� ���������): "<<endl;
			cout<<"4.����� �� ������������������ � ���� �������, �������� ���� ��������� �� ������� ����: "<<endl;
			cout<<"5.R����������������� �� �����, ����� �� �� ���� ����� ��� �����.(��� �������� ������): "<<endl;
			cin>>izbor;
		} while (!(izbor >= 1 && izbor <= 5));

		switch (izbor)
		{
		case 1:
		{
			//��������� �� ��������� �� �������, � �����, �� �������
			//��������� ������ ������ �� �������
			ElementsToList(vCRazprostranitel, lFilms, [](const CRazprostranitel& obj)
	{
		return obj.GetFilms().GetEdition() > 50000 && obj.GetFilms().GetGenre() == EnumG::comedy;});
		}
		break;
		case 2:
		{
			GetCommonProducers(vCRazprostranitel);
		}
		break;
		case 3:
		{
			PrintMoviesByProducerName(vCRazprostranitel, "KevinFeige");
		}
		break;
		case 4:
		{
			GetDistributorsByIncomes(vCRazprostranitel, "incomes.txt");
		}
		break;
		case 5:
		{
				GetDistributorsByYear(vCRazprostranitel, 2018);
		}
		break;
		default:
			break;
		}
		cout<<endl<<"������� �� �� ��������� ����� �������� (y/n) ?";
		cin>>choice2;
	} while (choice2 == 'y' || choice2 == 'Y');

	cout<<endl;
	system("pause");
}