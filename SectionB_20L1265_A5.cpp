#include <iostream>
#include <cstdlib>
#include <fstream>
#include <ctime>
#include <conio.h>
using namespace std;


void Deallocate_Memory(char **matrix, const int &rows)
{
	for (int i = 0; i < rows; i++)
	{
		if(matrix[i] != 0)
		delete[] matrix[i];
	}

	delete[] matrix;
}

void Allocate_Memory(char** &Grid, int Max, int No_Of_Words)
{
	Grid = new char* [No_Of_Words];
	for(int i = 0; i < No_Of_Words; i++)
	{
		Grid[i] = new char[Max];
	}

	for(int i = 0; i <  No_Of_Words; i++)
	{
		for(int j = 0; j < Max; j++)
		{
			Grid[i][j] = '-';
		}
	}
}

int strlength(char *string)
{
	int length = 0;
	for (char *temp = string; *temp != '\0'; temp++)
	{
		length++;
	}

	return length;
}

int SpaceCount(char *string)
{
	int counter = 0;
	for (char *temp = string; *temp != '\0'; temp++)
	{
		if(*(temp) == ' ')
		counter++;
	}

	return counter;
}

int GridWordsCounter(char** Grid, int Max, int No_Of_Words)
{
	int count = 0;
	for(int i = 0; i < No_Of_Words; i++)
	{
		for(int j = 0; j < Max; j++)
		{
			if(Grid[i][j] != '-')
				count++;
		}
	}

	return count;
}

int LetterCounter(char** Words, int No_Of_Words)
{
	int TotalLetters = 0;
	for(int i = 0; i < No_Of_Words; i++)
	{
		TotalLetters = TotalLetters+ strlength(Words[i]);
	}

	return TotalLetters;
}

char *DeepCopyIntoPointer(char *buffer)
{
	int Length = strlength(buffer) - SpaceCount(buffer);
	char *Char_Pointer = 0;

	if (Length > 0)
	{
		Char_Pointer = new char[Length + 1];
		char *temp_storing = Char_Pointer;
		for (char *temp_copy = buffer; *temp_copy != '\0'; temp_copy++)
		{
			if(*(temp_copy) != ' ')
			{
			   *temp_storing = *temp_copy;
			   temp_storing++;
			}
		}

		*temp_storing = '\0';
	}

	return Char_Pointer;
}

void SortWords(char** &Words,int No_Of_Words)
{
	for(int i = 0; i < No_Of_Words-1; i++)
	{
		for(int j = i+1; j < No_Of_Words; j++)
		{
			if(strlength(Words[i]) < strlength(Words[j]))
			{
				char* temp = DeepCopyIntoPointer(Words[i]);
				delete[] Words[i];
				Words[i] = DeepCopyIntoPointer(Words[j]);
				delete[] Words[j];
				Words[j] = DeepCopyIntoPointer(temp);
				delete[] temp;
			}
		}
	}
}

char* ReverseString(char* string)
{
	int length = strlength(string);
	char* result = new char[length];

	for(int i = 0, j = length-1; i <= length, j >= 0; j--, i++)
	{
		result[i] = string[j];
	}
	result[length] = '\0';
	return result;
}

bool SetLTR(char** &Grid , char* word, int Max, int No_Of_Words)
{
	int length = strlength(word);
	
	int counter = 0;
	int saveI = 0;
	int saveJ_start = 0;
	int saveJ_end = 0;
	bool end_check = false;
	for(int i = 0; i < No_Of_Words; i++)
	{
		counter = 0;
		for(int j = 0; j < Max; j++)
		{
			if(Grid[i][j] == '-')
			{
				if(counter == 0)
				saveJ_start = j;

				counter++;
			}
			if(Grid[i][j] != '-')
			{
				saveJ_start = 0;
				counter = 0;
			}
			if(counter == length)
			{
				saveJ_end = j;
				saveI = i;
				end_check = true;
				break;
			}
		}

		if(end_check == true)
			break;
	}

	if(end_check == true)
	{
		int index = 0;
		while(saveJ_start <= saveJ_end)
		{
			Grid[saveI][saveJ_start++] = word[index++];
		}
	}

	if(end_check == false)
	{
		return false;
	}

	return true;
}

bool SetRTL(char** &Grid , char* word, int Max, int No_Of_Words)
{
	char* Reversed = ReverseString(word);
	if(SetLTR(Grid,Reversed,Max,No_Of_Words) == true)
	{
		return true;
	}

	return false;
}

bool SetUTD(char** &Grid , char* word, int Max, int No_Of_Words)
{
	int length = strlength(word);
	
	int counter = 0;
	int saveI = 0;
	int saveJ_start = 0;
	int saveJ_end = 0;
	bool end_check = false;
	for(int i = 0; i < Max; i++)
	{
		counter = 0;
		for(int j = 0; j < No_Of_Words; j++)
		{
			if(Grid[j][i] == '-')
			{
				if(counter == 0)
				saveJ_start = j;

				counter++;
			}
			if(Grid[j][i] != '-')
			{
				saveJ_start = 0;
				counter = 0;
			}
			if(counter == length)
			{
				saveJ_end = j;
				saveI = i;
				end_check = true;
				break;
			}
		}

		if(end_check == true)
			break;
	}

	if(end_check == true)
	{
		int index = 0;
		while(saveJ_start <= saveJ_end)
		{
			Grid[saveJ_start++][saveI] = word[index++];
		}
	}

	if(end_check == false)
	{
		return false;
	}

	return true;
}

bool SetDTU(char** &Grid , char* word, int Max,int No_Of_Words)
{
	char* Reversed = ReverseString(word);
	if(SetUTD(Grid,Reversed,Max,No_Of_Words) == true)
	{
		return true;
	}

	return false;
}

bool SetDiagonal_TopL_to_BottomR(char** &Grid , char* word, int Max, int No_Of_Words)
{
	int length = strlength(word);
	
	int counter = 0;
	int saveI_start = 0;
	int saveI_end = 0;
	int saveJ_start = 0;
	int saveJ_end = 0;
	bool end_check = false;
	bool end_check_2 = false;

	for(int i = 0; i < Max; i++)
	{
		int backup_i = i;
		counter = 0;
		for(int j = 0; j < No_Of_Words , i < Max; j++)
		{
			if(Grid[j][i] == '-')
			{
				if(counter == 0)
				{
					saveJ_start = j;
					saveI_start = i;
				}
				counter++;
			}
			if(Grid[j][i] != '-')
			{
				saveJ_start = 0;
				saveI_start = 0;
				counter = 0;
			}

			if(counter == length)
			{
				saveJ_end = j;
				saveI_end = i;
				end_check = true;
				break;
			}
			i++;
		}
		i = backup_i;
		if(end_check == true)
			break;
	}

	if(end_check == true)
	{
		int index = 0;
		while(saveI_start <= saveI_end && saveJ_start <= saveJ_end)
		{
			Grid[saveJ_start++][saveI_start++] = word[index++];
		}
	}



	if(end_check == false)
	{
		for(int i = 0; i < No_Of_Words; i++)
		{
			int backup_i = i;
			counter = 0;
			for(int j = 0; j < Max, i < Max; j++)
			{
				
				if(Grid[i][j] == '-')
				{
					if(counter == 0)
					{
						saveJ_start = j;
						saveI_start = i;
					}
					counter++;
				}
				if(Grid[i][j] != '-')
				{
					saveJ_start = 0;
					saveI_start = 0;
					counter = 0;
				}

				if(counter == length)
				{
					saveJ_end = j;
					saveI_end = i;
					end_check_2 = true;
					break;
				}
				i++;
			}
			i = backup_i;
			if(end_check_2 == true)
				break;
		}
	}

	if(end_check_2 == true)
	{
		int index = 0;
		while(saveI_start <= saveI_end && saveJ_start <= saveJ_end)
		{
			Grid[saveI_start++][saveJ_start++] = word[index++];
		}
	}

	if(end_check == false && end_check_2 == false)
	{
		return false;
	}

	return true;
}

bool SetDiagonal_BottomR_to_TopL(char** &Grid , char* word, int Max,int No_Of_Words)
{
	char* Reversed = ReverseString(word);
	if(SetDiagonal_TopL_to_BottomR(Grid,Reversed,Max,No_Of_Words) == true)
	{
		return true;
	}

	return false;
}

bool SetDiagonal_BottomL_to_TopR(char** &Grid , char* word, int Max, int No_Of_Words)
{
	int length = strlength(word);
	
	int counter = 0;
	int saveI_start = 0;
	int saveI_end = 0;
	int saveJ_start = 0;
	int saveJ_end = 0;
	bool end_check = false;
	bool end_check_2 = false;

	for(int i = 0; i < Max; i++)
	{
		int backup_i = i;
		counter = 0;
		for(int j = No_Of_Words - 1; j > 0 , i < Max; j--)
		{
			if(Grid[j][i] == '-')
			{
				if(counter == 0)
				{
					saveJ_start = j;
					saveI_start = i;
				}
				counter++;
			}
			if(Grid[j][i] != '-')
			{
				saveJ_start = 0;
				saveI_start = 0;
				counter = 0;
			}

			if(counter == length)
			{
				saveJ_end = j;
				saveI_end = i;
				end_check = true;
				break;
			}
			i++;
		}
		i = backup_i;
		if(end_check == true)
			break;
	}

	if(end_check == true)
	{
		int index = 0;
		while(saveI_start <= saveI_end && saveJ_start >= saveJ_end)
		{
			Grid[saveJ_start--][saveI_start++] = word[index++];
		}
	}



	if(end_check == false)
	{
		for(int i = No_Of_Words - 1; i > 0; i--)
		{
			int backup_i = i;
			counter = 0;
			for(int j = 0; j < Max, i > 0; j++)
			{
				
				if(Grid[i][j] == '-')
				{
					if(counter == 0)
					{
						saveJ_start = j;
						saveI_start = i;
					}
					counter++;
				}
				if(Grid[i][j] != '-')
				{
					saveJ_start = 0;
					saveI_start = 0;
					counter = 0;
				}

				if(counter == length)
				{
					saveJ_end = j;
					saveI_end = i;
					end_check_2 = true;
					break;
				}
				i--;
			}
			i = backup_i;
			if(end_check_2 == true)
				break;
		}
	}

	if(end_check_2 == true)
	{
		int index = 0;
		while(saveI_start >= saveI_end && saveJ_start <= saveJ_end)
		{
			Grid[saveI_start--][saveJ_start++] = word[index++];
		}
	}

	if(end_check == false && end_check_2 == false)
	{
		return false;
	}

	return true;

}

bool SetDiagonal_TopR_to_BottomL(char** &Grid , char* word, int Max, int No_Of_Words)
{
	char* Reversed = ReverseString(word);
	if(SetDiagonal_BottomL_to_TopR(Grid,Reversed,Max,No_Of_Words) == true)
	{
		return true;
	}

	return false;
}

void PutWordsIntoGrid(char** &Grid, char* Word, int Max, int Pick, int No_Of_Words)
{

	if(Pick == 1)
	{
	  if(SetLTR(Grid,Word,Max, No_Of_Words) != true)
	  {
		 if(SetUTD(Grid,Word,Max, No_Of_Words) != true)
		 {
			 if(SetDiagonal_BottomL_to_TopR(Grid,Word,Max, No_Of_Words) != true)
			 {
				 SetDiagonal_TopL_to_BottomR(Grid,Word,Max,No_Of_Words);
			 }
		 }
	  }
	}

	if(Pick == 2)
	{
	  if(SetRTL(Grid,Word,Max,No_Of_Words) != true)
	  {
		 if(SetDTU(Grid,Word,Max,No_Of_Words) != true)
		 {
			 if(SetDiagonal_BottomR_to_TopL(Grid,Word,Max,No_Of_Words) != true)
			 {
				 SetDiagonal_TopR_to_BottomL(Grid,Word,Max,No_Of_Words);
			 }
		 }
	  }
	}

	if(Pick == 3)
	{
	  if(SetUTD(Grid,Word,Max, No_Of_Words) != true)
	  {
		 if(SetLTR(Grid,Word,Max, No_Of_Words) != true)
		 {
			 if(SetDiagonal_BottomL_to_TopR(Grid,Word,Max, No_Of_Words) != true)
			 {
				 SetDiagonal_TopL_to_BottomR(Grid,Word,Max, No_Of_Words);
			 }
		 }
	  }
	}

	if(Pick == 4)
	{
	  if(SetDTU(Grid,Word,Max,No_Of_Words) != true)
	  {
		 if(SetRTL(Grid,Word,Max,No_Of_Words) != true)
		 {
			 if(SetDiagonal_BottomR_to_TopL(Grid,Word,Max,No_Of_Words) != true)
			 {
				 SetDiagonal_TopR_to_BottomL(Grid,Word,Max,No_Of_Words);
			 }
		 }
	  }
	}

	if(Pick == 5)
	{
	  if(SetDiagonal_TopL_to_BottomR(Grid,Word,Max,No_Of_Words) != true)
	  {
		 if(SetDiagonal_BottomL_to_TopR(Grid,Word,Max,No_Of_Words) != true)
		 {
			 if(SetLTR(Grid,Word,Max,No_Of_Words) != true)
			 {
				 SetUTD(Grid,Word,Max,No_Of_Words);
			 }
		 }
	  }
	}

	if(Pick == 6)
	{
	  if(SetDiagonal_BottomR_to_TopL(Grid,Word,Max,No_Of_Words) != true)
	  {
		 if(SetDiagonal_TopR_to_BottomL(Grid,Word,Max,No_Of_Words) != true)
		 {
			 if(SetRTL(Grid,Word,Max,No_Of_Words) != true)
			 {
				 SetDTU(Grid,Word,Max,No_Of_Words);
			 }
		 }
	  }
	}

	if(Pick == 7)
	{
	  if(SetDiagonal_BottomL_to_TopR(Grid,Word,Max,No_Of_Words) != true)
	  {
		 if(SetDiagonal_TopL_to_BottomR(Grid,Word,Max,No_Of_Words) != true)
		 {
			 if(SetLTR(Grid,Word,Max,No_Of_Words) != true)
			 {
				 SetUTD(Grid,Word,Max,No_Of_Words);
			 }
		 }
	  }
	}

	if(Pick == 8)
	{
	  if(SetDiagonal_TopR_to_BottomL(Grid,Word,Max,No_Of_Words) != true)
	  {
		 if(SetDiagonal_BottomR_to_TopL(Grid,Word,Max,No_Of_Words) != true)
		 {
			 if(SetRTL(Grid,Word,Max,No_Of_Words) != true)
			 {
				 SetDTU(Grid,Word,Max,No_Of_Words);
			 }
		 }
	  }
	}

}

void FillRandomWords(char** &Grid, int Max, int No_Of_Words)
{
	
	srand((unsigned)time(0));

	for (int i = 0; i < No_Of_Words; i++)
	{
		for (int j = 0; j < Max; j++)
		{
			if (Grid[i][j] == '-')
			{
				Grid[i][j]= (char)((rand() % 26) + 65);
			}
		}
	}
}

bool CheckLTR(char **& grid, char *word, int rows, int cols, ofstream& OUT)
{ //Checks for the word in Left to Right direction in Grid and returns true or false accordingly//
	int index = 0;
	int counter = 0;
	int i_start = 0;
	int i_end = 0;
	int j_start = 0;
	int j_end = 0;
	int length = strlength(word);
	bool break_out = false;
	for (int i = 0; i < rows; i++)
	{
		index = 0;
		counter = 0;
		for (int j = 0; j < cols; j++)
		{
			int BackUp = index;
			if (grid[i][j] == word[index])
			{
				if (counter == 0)
				{
					i_start = i;
					j_start = j;
				}
				counter++;
				index++;
			}

			if (grid[i][j] != word[BackUp])
			{
				i_start = 0;
				j_start = 0;
				counter = 0;
				index = 0;
			}

			if (counter == length)
			{
				i_end = i;
				j_end = j;
				break_out = true;
				break;
			}
		}

		if (break_out == true)
			break;
	}

	if (break_out == true)
	{
		cout << "{" << i_start << "," << j_start << "}" << "," << "{" << i_end << "," << j_end << "}" << endl;
		OUT  << "{" << i_start << "," << j_start << "}" << "," << "{" << i_end << "," << j_end << "}" << endl;
		return true;
	}

	if (break_out == false)
	{
		return false;
	}

	return false;
}

bool CheckUTD(char **& grid, char *word, int rows, int cols,ofstream& OUT)
{ //Checks for the word in Up to Down direction in Grid and returns true or false accordingly//
	int index = 0;
	int counter = 0;
	int i_start = 0;
	int i_end = 0;
	int j_start = 0;
	int j_end = 0;
	int length = strlength(word);
	bool break_out = false;
	for (int i = 0; i < rows; i++)
	{
		index = 0;
		counter = 0;
		for (int j = 0; j < cols; j++)
		{
			int BackUp = index;
			if (grid[j][i] == word[index])
			{
				if (counter == 0)
				{
					i_start = i;
					j_start = j;
				}
				counter++;
				index++;
			}

			if (grid[j][i] != word[BackUp])
			{
				i_start = 0;
				j_start = 0;
				counter = 0;
				index = 0;
			}

			if (counter == length)
			{
				i_end = i;
				j_end = j;
				break_out = true;
				break;
			}
		}

		if (break_out == true)
			break;
	}

	if (break_out == true)
	{
		cout << "{" << j_start << "," << i_start << "}" << "," << "{" << j_end << "," << i_end << "}" << endl;
		OUT  << "{" << j_start << "," << i_start << "}" << "," << "{" << j_end << "," << i_end << "}" << endl;
		return true;
	}

	if (break_out == false)
	{
		return false;
	}

	return false;
}

bool CheckDiagonal_TopL_to_BottomR(char **& grid, char *word, int rows, int cols, ofstream& OUT)
{ //Checks for the word in Top Left to Bottom Right diagonal of Grid and returns true or false accordingly//
	int index = 0;
	int counter = 0;
	int i_start = 0;
	int i_end = 0;
	int j_start = 0;
	int j_end = 0;
	int length = strlength(word);
	bool break_out = false;
	bool break_out_2 = false;

	for (int i = 0; i < cols; i++)
	{
		int backup_i = i;
		counter = 0;
		for (int j = 0; j<rows, i < rows; j++)
		{
			int BackUp = index;
			if (grid[j][i] == word[index])
			{
				if (counter == 0)
				{
					i_start = i;
					j_start = j;
				}
				counter++;
				index++;
			}

			if (grid[j][i] != word[BackUp])
			{
				i_start = 0;
				j_start = 0;
				counter = 0;
				index = 0;
			}

			if (counter == length)
			{
				i_end = i;
				j_end = j;
				break_out = true;
				break;
			}
			i++;
		}

		i = backup_i;
		if (break_out == true)
			break;
	}

	if (break_out == true)
	{
		cout << "{" << j_start << "," << i_start << "}" << "," << "{" << j_end << "," << i_end << "}" << endl;
		OUT  << "{" << j_start << "," << i_start << "}" << "," << "{" << j_end << "," << i_end << "}" << endl;
		return true;
	}

	if (break_out == false)
	{ //This is to check the lower side of main diagonal if nothing is found after checking upper side//
		for (int i = 0; i < rows; i++)
		{
			int backup_i = i;
			counter = 0;
			for (int j = 0; j<rows, i < rows; j++)
			{
				int BackUp = index;
				if (grid[i][j] == word[index])
				{
					if (counter == 0)
					{
						i_start = i;
						j_start = j;
					}
					counter++;
					index++;
				}

				if (grid[i][j] != word[BackUp])
				{
					i_start = 0;
					j_start = 0;
					counter = 0;
					index = 0;
				}

				if (counter == length)
				{
					i_end = i;
					j_end = j;
					break_out_2 = true;
					break;
				}
				i++;
			}
			i = backup_i;
			if (break_out_2 == true)
				break;
		}
	}

	if (break_out_2 == true)
	{
		cout << "{" << i_start << "," << j_start << "}" << "," << "{" << i_end << "," << j_end << "}" << endl;
		OUT  << "{" << i_start << "," << j_start << "}" << "," << "{" << i_end << "," << j_end << "}" << endl;
		return true;
	}

	if (break_out == false && break_out_2 == false)
	{
		return false;
	}

	return false;
}

bool CheckDiagonal_BottomL_to_TopR(char **& grid, char *&word, int rows, int cols, ofstream& OUT)
{ //Checks for the word in Bottom Left to Top Right diagonal of Grid and returns true or false accordingly//
	int index = 0;
	int counter = 0;
	int i_start = 0;
	int i_end = 0;
	int j_start = 0;
	int j_end = 0;
	int length = strlength(word);
	bool break_out = false;
	bool break_out_2 = false;

	for (int i = 0; i < cols; i++)
	{
		int backup_i = i;
		counter = 0;
		for (int j = rows - 1; j > 0, i < cols; j--)
		{
			int BackUp = index;
			if (grid[j][i] == word[index])
			{
				if (counter == 0)
				{
					i_start = i;
					j_start = j;
				}
				counter++;
				index++;
			}

			if (grid[j][i] != word[BackUp])
			{
				i_start = 0;
				j_start = 0;
				counter = 0;
				index = 0;
			}

			if (counter == length)
			{
				i_end = i;
				j_end = j;
				break_out = true;
				break;
			}
			i++;
		}
		i = backup_i;
		if (break_out == true)
			break;
	}

	if (break_out == true)
	{
		cout << "{" << j_start << "," << i_start << "}" << "," << "{" << j_end << "," << i_end << "}" << endl;
		OUT  << "{" << j_start << "," << i_start << "}" << "," << "{" << j_end << "," << i_end << "}" << endl;
		return true;
	}

	if (break_out == false)
	{ //This is to check the lower side of initial diagonal if nothing is found after checking upper side//
		for (int i = cols - 1; i > 0; i--)
		{
			int backup_i = i;
			counter = 0;
			for (int j = 0; j<cols, i> 0; j++)
			{

				int BackUp = index;
				if (grid[i][j] == word[index])
				{
					if (counter == 0)
					{
						i_start = i;
						j_start = j;
					}
					counter++;
					index++;
				}

				if (grid[i][j] != word[BackUp])
				{
					i_start = 0;
					j_start = 0;
					counter = 0;
					index = 0;
				}

				if (counter == length)
				{
					i_end = i;
					j_end = j;
					break_out_2 = true;
					break;
				}
				i--;
			}
			i = backup_i;
			if (break_out_2 == true)
				break;
		}
	}

	if (break_out_2 == true)
	{
		cout << "{" << i_start << "," << j_start << "}" << "," << "{" << i_end << "," << j_end << "}" << endl;
		OUT  << "{" << i_start << "," << j_start << "}" << "," << "{" << i_end << "," << j_end << "}" << endl;
		return true;
	}

	if (break_out == false && break_out_2 == false)
	{
		return false;
	}

	return false;
}

bool CheckRTL(char **& Grid, char *word, int rows, int cols, ofstream& OUT)
{ //Reverses the word and then calls CheckLTR which this time ultimately checks for Right to Left direction instead//
	char *Reversed = ReverseString(word);

	if (CheckLTR(Grid, Reversed, rows, cols, OUT) == true)
	{
		return true;
	}

	return false;
}

bool CheckDTU(char **& Grid, char *word, int rows, int cols, ofstream& OUT)
{ //Reverses the word and then calls CheckUTD which this time ultimately checks for Down to Up direction instead//
	char *Reversed = ReverseString(word);

	if (CheckUTD(Grid, Reversed, rows, cols, OUT) == true)
	{
		return true;
	}

	return false;
}

bool CheckDiagonal_BottomR_to_TopL(char **& Grid, char *word, int rows, int cols, ofstream& OUT)
{//Reverses the word and then calls CheckDiagonal_TopL_to_BottomR which this time checks for the diagonal in opposite direction instead//
	char *Reversed = ReverseString(word);

	if (CheckDiagonal_TopL_to_BottomR(Grid, Reversed, rows, cols, OUT) == true)
	{
		return true;
	}

	return false;
}

bool CheckDiagonal_TopR_to_BottomL(char **& Grid, char *word, int rows, int cols,ofstream& OUT)
{//Reverses the word and then calls CheckDiagonal_BottomL_to_TopR which this time checks for the diagonal in opposite direction instead//
	char *Reversed = ReverseString(word);

	if (CheckDiagonal_BottomL_to_TopR(Grid, Reversed, rows, cols, OUT) == true)
	{
		return true;
	}

	return false;
}

void CheckAll(char **& Grid, char *word, int rows, int cols, ofstream& OUT)
{ //This function combines all the previous checks together so that they can be conveniently called in main//
	//Also responsible for displaying "Not Found"//

	if ((CheckLTR(Grid, word, rows, cols, OUT) == false) && (CheckRTL(Grid, word, rows, cols, OUT) == false) && (CheckUTD(Grid, word, rows, cols, OUT) == false) && (CheckDTU(Grid, word, rows, cols, OUT) == false) && (CheckDiagonal_BottomL_to_TopR(Grid, word, rows, cols, OUT) == false) && (CheckDiagonal_BottomR_to_TopL(Grid, word, rows, cols,OUT) == false) && (CheckDiagonal_TopL_to_BottomR(Grid, word, rows, cols, OUT) == false) && (CheckDiagonal_TopR_to_BottomL(Grid, word, rows, cols,OUT) == false))
	{
		cout << "Not Found" << endl;
	}
}

int CreateGrid(char temp[20],char temp2[20], int numOfWords, int rows, int cols)
{
	ifstream inp (temp);
	
	if(!inp)
	{
		cout<<"Error while reading input: Check your File"<<endl;
		system("pause");
		return 0;
	}


	int No_Of_Words = numOfWords;
	if(rows < No_Of_Words)
	{
		cout<<"Grid cannot be formed, ";
		system("pause");
		return 0;
	}


	char** Temp = new char*[30];
	int i = 0;
	while(!inp.eof())
	{
		char temp[20];
		inp.getline(temp,20);
		Temp[i++] = DeepCopyIntoPointer(temp);
	}

	char** Words = new char* [No_Of_Words];
	for(int i = 0; i < No_Of_Words; i++)
	{
		Words[i] = DeepCopyIntoPointer(Temp[i]);
	}
	Deallocate_Memory(Temp,No_Of_Words);
	
	int Max = strlength(Words[0]);
	for(int i = 0; i < No_Of_Words; i++)
	{	
		if(strlength(Words[i]) > Max)
		{
		  Max = strlength(Words[i]);
		}
	}

	if(cols < Max)
	{
		cout<<"Grid cannot be formed, ";
		system("pause");
		return 0;
	}


	int TotalLetters = LetterCounter(Words,No_Of_Words);
	char** Grid = 0;
	Allocate_Memory(Grid,cols,rows);
	SortWords(Words,No_Of_Words);

	srand((unsigned)time(0));
	while( GridWordsCounter(Grid,cols,rows) != TotalLetters)
	{
		Deallocate_Memory(Grid,rows);
		Allocate_Memory(Grid,cols,rows);

		for(int i = 0; i <  No_Of_Words; i++)
		{
			int Pick = rand() % 8 + 1;;
			PutWordsIntoGrid(Grid,Words[i],cols,Pick,rows);
		}
	}

	FillRandomWords(Grid,cols,rows);


	ofstream OUT (temp2);

	for(int i = 0; i <  rows; i++)
	{
		for(int j = 0; j < cols; j++)
		{
			OUT<<Grid[i][j];
		}
		OUT<<endl;
	}
	inp.close();
	OUT.close();

	Deallocate_Memory(Grid,No_Of_Words);
	Deallocate_Memory(Words,No_Of_Words);

	cout<<"Output Grid Successfully Generated!!"<<endl;
	return 1;

}

int SearchGrid(char temp[20], char temp2[20], char tempOUT[20])
{

	ifstream fin(temp2);
	int Rows = 0;
	int Cols = 0;
	fin >> Rows >> Cols;

	int testCases = 0;
	fin >> testCases;

	fin.ignore(100, '\n'); //To avoid problems with getline//
	cout << endl;
	char **InputWords = new char *[testCases];
	for (int i = 0; i < testCases; i++)
	{
		char Temp[30];
		fin.getline(Temp, 30);
		InputWords[i] = DeepCopyIntoPointer(Temp); 
	}

	char **Grid = new char *[Rows];
	ifstream inp (temp);
	for (int r = 0; r < Rows; r++)
	{
		Grid[r] = new char[Cols];
		char Temp[30];
		inp.getline(Temp, 30);
		Grid[r] = DeepCopyIntoPointer(Temp);
	}

	cout << endl << "THE GRID :- " << endl;

	for (int r = 0; r < Rows; r++)
	{
		for (int c = 0; c < Cols; c++)
		{
			cout << Grid[r][c] << "\t";
		}
		cout << endl;
	}

	cout << endl << "RESULT OF THE SEARCH: " << endl;

	ofstream OUT (tempOUT);
	for (int r = 0; r < testCases; r++)
	{
		CheckAll(Grid, InputWords[r], Rows, Cols,OUT); //Simple loop that index by index sends the given words through all checks//
	}

	Deallocate_Memory(Grid, Rows);
	Deallocate_Memory(InputWords, testCases);

	cout << endl;
	return 1;
}

int main()
{

	char choice = ' ';
	while(choice != 'Q' && choice != '3')
	{
		system("CLS");
		cout<<"   ***MAIN MENU***  "<<endl<<endl;
		cout<<"1) Create Grid (Enter C or 1)"<<endl;
		cout<<"2) Search Words from Grid (Enter S or 2)"<<endl;
		cout<<"3) Quit (Enter Q or 3)"<<endl<<endl;
		cout<<"Enter your choice: ";
		cin >> choice;

		if(choice == 'C' || choice == '1' )
		{
			system("CLS");
			cout<<"GRID CREATER HAS STARTED SUCCESSFULLY!!"<<endl<<endl;
			cout<<"Kindly provide the required information: "<<endl<<endl;

			cin.ignore();
			char Name[20];
			cout<<"Name of the Input File (For WORDS): ";
			cin.getline(Name,20);

			int numOfWords;
			cout<<endl<<"Total Number of Words in the file: ";
			cin>>numOfWords;

			int Rows;
			cout<<endl<<"Number of rows in the grid: ";
			cin>>Rows;

			int Cols;
			cout<<endl<<"Number of columns in the grid: ";
			cin>>Cols;

			cin.ignore();
			char NameOUT[20];
			cout<<endl<<"Name of the Output File for Grid: ";
			cin.getline(NameOUT,20);

			if(CreateGrid(Name,NameOUT,numOfWords,Rows,Cols) == 1)
			{
				cout<<endl<<endl;
				system("pause");
			}
		}

		if(choice == 'S' || choice == '2')
		{
			system("CLS");
			cout<<"WORD SEARCHER HAS STARTED SUCCESSFULLY!!"<<endl<<endl;
			cout<<"Kindly provide the required information: "<<endl<<endl;

			cin.ignore();
			char Name[20];
			cout<<"Name of the Input File (For GRID): ";
			cin.getline(Name,20);

			char NameDATA[20];
			cout<<endl<<"Name of the Input File for Data: ";
			cin.getline(NameDATA,20);

			char NameOUT[20];
			cout<<endl<<"Name of the Output file where the results needs to be placed: ";
			cin.getline(NameOUT,20);

			if(SearchGrid(Name,NameDATA,NameOUT) == 1)
			{
				cout<<endl<<endl;
				system("pause");
			}

		}

		if(choice == 'Q' || choice == '3' )
		{
			cout<<endl<<"Quitting the Program....."<<endl; 
			cout<<"Goodbye!!"<<endl;
		}
	}
	
	return 0;
}
