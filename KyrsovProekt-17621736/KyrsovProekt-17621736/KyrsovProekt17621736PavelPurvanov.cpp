#include <iostream>
#include <string>
#include <time.h>
#include <fstream>
#include <vector>
#include <list>
#include <algorithm>
#include <map>
using namespace std;

//енум за жанровете
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
	string MTitle;//заглавие на филма
	string MProducer;//продуцент
	int MEdition;//тираж
	int MYear;//година на издаване
	EnumG MGenre;//жанр

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

	//1.Валидизиране на жанра
	bool ValidationGenre()
	{return !GetGenre(MGenre).empty();}

	//2.Изчислява възрастта на филма/използваме ф-я GetCurrentYear
	int GetMAge()
	{return GetCurrentYear() - MYear;}

	//3.Извеждане данните за филма на принтер
	void Printer(const string& FName)
	{
		ofstream file(FName);
		PrintFile(file);
		file.close();
	}

	//4.Оператор за присвояване
	CFilms& operator = (const CFilms& obj)
	{
		this->MTitle = obj.MTitle;
		this->MProducer = obj.MProducer;
		this->MEdition = obj.MEdition;
		this->MYear = obj.MYear;
		this->MGenre = obj.MGenre;

		return *this;
	}

	//5.Логически оператор, проверяващ дали филмът е създаден през текущата година
	bool operator == (const CFilms& obj)
	{
		return obj.MYear == GetCurrentYear();
	}

	//6.Оператор за сравнение > (по тираж(Edition))
	friend bool operator >(const CFilms& obj, const CFilms& jbo)
	{
		return obj.MEdition == jbo.MEdition;
	}

	//7.Оператор за съвпадение (по продуцент(Producer))
	friend bool operator == (const CFilms& obj, const CFilms& jbo)
	{
		return obj.MProducer == jbo.MProducer;
	}

protected:

	//статична функцията, която при подаден жанр(енум), връща жанра под формата на стринг
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

	//шаблонна функцията, която се ползва за извеждане на конзола и файл
	template<typename T>
	void Print(T& stream)
	{
		stream << "\nЗаглавие на филма: " << MTitle
			<< " Продуцент: " << MProducer
			<< " Тираж: " << MEdition
			<< " Година на издаване: " << MYear
			<< " Жанр: " << GetGenre(MGenre) << endl;
	}

	//функция която връща текущата година, необходима за реализиране на 2.Изчислява възрастта на филма
	int GetCurrentYear()const
	{
		time_t Time = time(NULL);
		tm *aTime = localtime(&Time);

		int nCurrentYear = aTime->tm_year + 1900;

		return nCurrentYear;
	}
};

//клас разпространител
class CRazprostranitel
{
private:
	CFilms MFilms;//филми
	string MRazprostranitel;//име на разпространителя
	int MCount;//броя продадени филми
	double MIncomes;//приходи за година

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

	//copy constructor/1.Създаване на обект чрез друг обект.
	CRazprostranitel(const CRazprostranitel& object)
	{
		MFilms = object.MFilms;
		MRazprostranitel = object.MRazprostranitel;
		MCount = object.MCount;
		MIncomes = object.MIncomes;
	}
	
	//2.Функция, определяща дали филмът е предлаган повече от веднъж.
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

	//оператор за извеждане в поток
	friend ostream & operator <<(ostream& out, const CRazprostranitel& jbo)
	{
		out << "\nИме на разпространител: " << jbo.MRazprostranitel
			<< " Брой филми: " << jbo.MCount
			<< " Приходи за една година: " << jbo.MIncomes;

		jbo.GetFilms().PrintConsole(out);

		return out;
	}

};

// за да избегнем писането на "vector<CRazprostranitel>", когато ни е необходимо.
typedef vector<CRazprostranitel> vCRazprostranitel;

//шаблонна функцията, за добавяне на елементи в листа.
//Необходима за реализирането на 1.Извеждане на филмите с тираж на 50 000 копия от жанр комедия.
template<typename func>
void ElementsToList(const vCRazprostranitel& vCRazprostranitel, list<CFilms>& lFilms, func condition)
{
	vCRazprostranitel::const_iterator iter = vCRazprostranitel.begin();

	while ((iter = find_if(iter, vCRazprostranitel.end(), condition)) != vCRazprostranitel.end())
	{
		lFilms.push_back(iter->GetFilms());

		++iter;
	}
	cout<<"Листът беше създаден."<<endl;
}

//функция, която пълни вектора с данни от файла (strFileName), връща false, ако има проблем с файла
bool GetFromFile(const string& strFileName, vCRazprostranitel& vCRazprostranitel)
{
	ifstream file;

	file.open(strFileName);

	if (!file.is_open())
		return false;

	string strMovieTitle, strMovieProducer, strDistributorName;
	int nDrawing = 0, nYear = 0, nGenre = 0, nMoviesCount = 0;
	double dIncomeForOneYear;

	//четене на данните от файла, ред по ред
	while (file >> strMovieProducer >> strMovieTitle >> nDrawing >> nYear >> nGenre >> strDistributorName >> nMoviesCount >> dIncomeForOneYear)
	{
		//създаване на обект филми
		CFilms oFilms(strMovieTitle, strMovieProducer, nDrawing, nYear, (EnumG)nGenre);

		//добавяне във вектора
		vCRazprostranitel.emplace_back(CRazprostranitel(oFilms, strDistributorName, nMoviesCount, dIncomeForOneYear));
	}
	
	//затваряне на файла
	file.close();

	
	return true;
}

//2. Да се изведат в отделни файлове всички разпорстранители, които разпространяват 
//филми на едни и същи продуценти
void GetCommonProducers(const vCRazprostranitel& vCRazprostranitel)
{
	//името на всеки файла ще се генерира както следва: File1,2,3,4,5 и т.н.
	string strFileName = "File";
	int nCounter = 1;

	//използвам map за съхранение на двойки ключ-стойност -> продуцент-вектор със дистрибутори
	map<string, vector<string>> mProducerKeys;

	//пълнене на картата
	for (auto it = vCRazprostranitel.begin(); it != vCRazprostranitel.end(); ++it)
	{
		mProducerKeys[it->GetFilms().GetProducer()].emplace_back(it->GetRName());
	}

	//възползвам се от това че елементите (ключовете) са сортирани низходящо
	//и обхождам мап-а докато размера на вектора е по-голям или равен на 2, защото няма смисъл да обхождам другите записи
	for (auto it = mProducerKeys.begin(); it->second.size() >= 2; ++it)
	{
		ofstream file(strFileName + to_string(nCounter++) + ".txt");

		file << "Продуцент: " << it->first << endl;

		for (auto vIt = it->second.begin(); vIt != it->second.end(); ++vIt)
		{
			file << "Разпространител: " << *vIt << endl;
		}

		file.close();
	}
	cout<<"Файловете бяха създадени."<<endl;
}

//3.Да се изведат заглавията на филмите, които са над 20 за продуцент,
//чието име е подадено като параметър.
void PrintMoviesByProducerName(const vCRazprostranitel& vCRazprostranitel, const string& strProducerName)
{
	const int MOVIES_COUNT = 20;
	vCRazprostranitel::const_iterator iter = vCRazprostranitel.begin();

	//докато има елементи във вектора, които отговарят на условието
	//използване на ламбда израз(Анонимна функция)
	while ((iter = find_if(iter, vCRazprostranitel.end(), [&strProducerName, &MOVIES_COUNT](const CRazprostranitel& obj)
	{
		return obj.GetFilms().GetProducer() == strProducerName && obj.GetMoviesCount() > MOVIES_COUNT;

	})) != vCRazprostranitel.end())
	{
		//ако има намерен елемент, извеждам данните
		iter->GetFilms().PrintConsole(cout);

		//инкрементирам итератора
		//префикс инкрементация, за да се избегне викането на конструктора на CRazprostranitel при всяка инкрементация
		++iter;
	}
}

//4.Да се изведат всички данни за разпространителите с брой приходи,
//получени като параметър от текстов файл.
bool GetDistributorsByIncomes(const vCRazprostranitel& vCRazprostranitel, const string& strFileName)
{
	//отваряне на файла
	ifstream file;

	file.open(strFileName);

	if (!file.is_open())
		return false;

	double dIncome;

	//четене на стойността за приходи по които ще намираме записите
	file >> dIncome;

	file.close();

	//итератор за началото на вектора
	vCRazprostranitel::const_iterator iter = vCRazprostranitel.begin();

	//метода който ползвам, е същият като в горната функция
	while ((iter = find_if(iter, vCRazprostranitel.end(), [&dIncome](const CRazprostranitel& obj)
	{
		return obj.GetIncome() == dIncome;

	})) != vCRazprostranitel.end())
	{
		cout << *iter;

		++iter;
	}
}

//5.При подаден параметър година на производство, да се изведат разпространителите на
//такива филми, които са от жанр екшън или драма.
void GetDistributorsByYear(const vCRazprostranitel& vCRazprostranitel, int nYear)
{
	//отново същият метод за намиране на точните записи по година и жанр
	vCRazprostranitel::const_iterator iter = vCRazprostranitel.begin();

	while ((iter = find_if(iter, vCRazprostranitel.end(), [&nYear](const CRazprostranitel& obj)
	{
		return obj.GetFilms().GetYear() == nYear
			&& (obj.GetFilms().GetGenre() == EnumG::action || obj.GetFilms().GetGenre() == EnumG::drama);

	})) != vCRazprostranitel.end())
	{
		//извеждане на името на дистрибутора
		cout << "\nРазпространител: " << iter->GetRName();

		++iter;
	}
}


int main()
{
	setlocale(LC_ALL, "Bulgarian");

	//създаване на вектор от обекти
	vCRazprostranitel vCRazprostranitel;

	//създаване на списък от филми
	list<CFilms>lFilms;

	//запазване на място за 10 елемента, за да се избегнат ненужни алокации на памет
	//хубаво .reserve да се използва винаги, когато знаем колко на брой елементи ще добавяме в контейнера
	vCRazprostranitel.reserve(10);

	//четем от файла,чрез функция (GetFromFile), за да избегнем писане на данни на "ръка"
	if (!GetFromFile("movies.txt", vCRazprostranitel))
		return _CRT_ERROR;

	char choice, choice2;
	int izbor;
	do {
		do {//главно меню
			cout<<"1.Извеждане в list филмите с тираж над 50000 копия от жанр комедия: "<<endl;
			cout<<"2.Извеждане в отделни файлове всички разпорстранители, които разпространяват филми на едни и същи продуценти: "<<endl;
			cout<<"3.Заглавията на филмите, които са над 20 за продуцент(подаден като параметър): "<<endl;
			cout<<"4.Данни за разпространителите с брой приходи, получени като параметър от текстов файл: "<<endl;
			cout<<"5.Rазпространителите на филми, които са от жанр екшън или драма.(при подадена година): "<<endl;
			cin>>izbor;
		} while (!(izbor >= 1 && izbor <= 5));

		switch (izbor)
		{
		case 1:
		{
			//добавявне на елментите от вектора, в листа, по условие
			//функцяита приема ламбда за условие
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
		cout<<endl<<"Желаете ли да направите друга операция (y/n) ?";
		cin>>choice2;
	} while (choice2 == 'y' || choice2 == 'Y');

	cout<<endl;
	system("pause");
}