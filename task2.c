//Программа позволяет получить время жизни пользователя в секундах
//Ввод имеет строго определенный формат
//В случае неверного ввода, предлагается повторить попытку
#include <stdio.h>
#include <time.h>
#include <string.h>
#include <stdlib.h>
//Перечисление - пользовательский тип данных для обозначения месяцев.
enum month_e{Jan = 1, Feb, Mar, Apr, May, Jun, Jul, Aug, Sept, Oct, Nov, Dec};
//Структура, определяющая дату рождения, которая хранит день, месяц, год, час, минуту рождения.
typedef struct _date_of_birth
{
	int day;
	int month;
	int year;
	int hour;
	int minute;
}date_of_birth;

typedef unsigned short BOOL;
#define FALSE 0
#define TRUE 1

BOOL validate_date_of_birth(date_of_birth users_birthday, time_t curr_time)
{
	
	struct tm *curr_time_struct;
	int min_year = 1900;
	curr_time_struct = localtime (&curr_time);
	
	if(users_birthday.year>curr_time_struct->tm_year+min_year||users_birthday.year<min_year)
	{
		printf("date is not correct: check year (after 1900)\n");
		return FALSE;
	}
	else
	{
		//общая проверка на месяц
		if(users_birthday.month<Jan||users_birthday.month>Dec)
		{
			printf("date is not correct: check month\n");
			return FALSE;
		}
		//конкретно по месяцам
		if((users_birthday.month==Apr||users_birthday.month==Jun||
			users_birthday.month==Sept||users_birthday.month==Nov)&&users_birthday.day>=31)
		{
			printf("date is not correct: check day\n");
			return FALSE;
		}
		else if(users_birthday.month==Feb)
		{
			//отдельно февраль
			if( (users_birthday.year%4==0 && users_birthday.year%100!=0) || (users_birthday.year%100==0 && users_birthday.year%400==0 ) )
			{
				//високосный
				if(users_birthday.day>29)
				{
					printf("date is not correct: check day\n");
					return FALSE;
				}
			}
			else if(users_birthday.day>28)
			{
				printf("date is not correct: check day\n");
				return FALSE;
			}
		}
		else if(users_birthday.day>31)
		{
			//все остальные
			printf("date is not correct: check day\n");
			return FALSE;
		}
		//проверка на час
		if(users_birthday.hour<0||users_birthday.hour>23)
		{
				printf("date is not correct: check hour\n");
				return FALSE;
		}
		//проверка минут
		if(users_birthday.minute>=60||users_birthday.minute<0)
		{
			printf("date is not correct: check minute\n");
			return FALSE;
		}
	}
	if(users_birthday.year==curr_time_struct->tm_year + min_year)
	{
		if(users_birthday.month>curr_time_struct->tm_mon+1)
		{
			printf("date is in the future\n");
			return FALSE;
		}
		else if(users_birthday.month==curr_time_struct->tm_mon+1)
		{
			if(users_birthday.day > curr_time_struct->tm_mday)
			{
				printf("date is in the future\n");
				return FALSE;
			}
			else if(users_birthday.day == curr_time_struct->tm_mday)
			{
				if(users_birthday.minute>curr_time_struct->tm_min)
				{
					printf("date is in the future\n");
					return FALSE;
				}

			}

		}
		//проверка, не позже ли дата рождения, чем сейчас.
	}
	return TRUE;
	
}

void write_date_of_birth(date_of_birth *users_birthday,char date_of_birth_str[17])
{
	//dd.mm.yyyy hh:mm
	char buf[5];
	memset(buf, 0, sizeof(buf)); 
	strncpy(buf, date_of_birth_str,2);
	users_birthday->day = atoi(buf);

	memset(buf, 0, sizeof(buf)); 
	strncpy(buf, &date_of_birth_str[3],2);
	users_birthday->month = atoi(buf);

	memset(buf, 0, sizeof(buf)); 
	strncpy(buf, (date_of_birth_str+6),4);
	users_birthday->year = atoi(buf);

	memset(buf, 0, sizeof(buf)); 
	strncpy(buf, (date_of_birth_str+11),2);
	users_birthday->hour = atoi(buf);

	strncpy(buf, (date_of_birth_str+14),2);
	users_birthday->minute = atoi(buf);
	memset(buf, 0, sizeof(buf)); 

}
BOOL validate_str_date_of_birth(char* birthday)
{
	//dd.mm.yyyy hh:mm
	int length = 16;
	int i = 0;
	if(strlen(birthday)!=length)
	{
		return FALSE;
	}
	if(birthday[2]!='.'||birthday[5]!='.'||birthday[10]!=' '||birthday[13]!=':')
	{
		return FALSE;
	}
	for(i = 0; i<length; i++)
	{
		if((birthday[i]>'9'||birthday[i]<'0')&&(i!=2)&&(i!=5)&&(i!=10)&&(i!=13))
			return FALSE;
	}

	return TRUE;
}
long long count_in_seconds(date_of_birth users_birthday, time_t curr_time)
{	
	struct tm *curr_time_struct;
	int min_year = 1900;
	long long from_year_beg_curr = 0;
	long long from_year_beg_user = 0;
	int i = 1;
	int i_0 =0;
	int i_1 =0;
	int numb_not_vis =0;
	long long seconds =0;
	int  numb_vis = 0;
	curr_time_struct = localtime (&curr_time);

	//прибавили сколько прошло с начала года
	from_year_beg_curr += curr_time_struct->tm_sec;
	from_year_beg_curr += curr_time_struct->tm_min*60;
	from_year_beg_curr += curr_time_struct->tm_hour*60*60;
	from_year_beg_curr += curr_time_struct->tm_yday*24*60*60;

	from_year_beg_user += users_birthday.minute*60;
	from_year_beg_user += users_birthday.hour*60*60;
	from_year_beg_user += (users_birthday.day-1)*24*60*60;

	while(i<users_birthday.month)
	{
		if(i==Apr||i==Jun||i==Sept||i==Nov)
		{
			from_year_beg_user += 30*24*60*60;
		}
		else if(i==Feb)
		{
			if( (users_birthday.year%4==0 && users_birthday.year%100!=0) || (users_birthday.year%100==0 && users_birthday.year%400==0 ) )
			{
				from_year_beg_user += 29*24*60*60;
						//високосный
			}
			else
			{
				from_year_beg_user += 28*24*60*60;
			}
		}
		else
		{
			from_year_beg_user += 31*24*60*60;
		}
		i++;
	}

	//годы между
	i_0 = users_birthday.year/4;
	if(users_birthday.year%4==0)
		i_0--;
	i_1 = (curr_time_struct->tm_year-1+min_year)/4;
	numb_vis= i_1-i_0;

	i_0  = users_birthday.year/100;
	if(users_birthday.year%100==0)
	i_0--;
	//текущий год учитываем не полностью - 1
	//год рождения - полностью, отнимая не прожитое в нём время
	i_1 = (curr_time_struct->tm_year-1+min_year)/100;
	numb_vis = numb_vis-(i_1-i_0);
	i_0  = users_birthday.year/400;
	if(users_birthday.year%400==0)
		i_0--;
	i_1 = (curr_time_struct->tm_year-1+min_year)/400;
	numb_vis = numb_vis+(i_1-i_0);
	numb_not_vis = (curr_time_struct->tm_year+min_year - users_birthday.year) - numb_vis;
	seconds = 0;
	seconds += 366*numb_vis*24*60*60;
	seconds += 365*numb_not_vis*24*60*60;
	seconds += from_year_beg_curr;
	seconds -= from_year_beg_user;
	return seconds;

}
int main()
{
	
	time_t curr_time = 0;
	date_of_birth* users_birthday = (date_of_birth*) malloc(sizeof(date_of_birth));
	BOOL end = 0;
	struct tm *timeinfo;

	time (&curr_time);
	timeinfo = localtime(&curr_time);
	printf ("Current local time and date: %s\n", asctime(timeinfo));


	while(!end)
	{
		char birthday[17];
		memset(birthday, 0, sizeof(birthday)); 
		printf ("Enter your date of birth as dd.mm.yyyy hh:mm\nEnter 0 to escape\n");
		if(fgets(birthday,17,stdin))
		{
	
			if((strlen(birthday)==2)&&(birthday[0]=='0'))
				break;

			if(validate_str_date_of_birth(birthday))
			{
				write_date_of_birth(users_birthday,birthday);
				if(validate_date_of_birth(*users_birthday, curr_time))
				{
					long long age_in_seconds = count_in_seconds(*users_birthday,curr_time);
					print("Age in seconds: %lld\n",age_in_seconds);
					end = TRUE;
					break;
				}
			}
			else
			{
				printf ("Formatt is not correct\n");
			}
			
		}
		printf("Try again!\n");
	}
 
	free(users_birthday );
	return 0;
}

