#include <string>
#include <iostream>
#include <string.h>

// res points to the substr
// // return code 1 means finish,
// // return code 0 means it still has substr

int strtok_a (char *src, char ** res, const char *delim, char **save_ptr)
{
	char *end;

	if (src == NULL)
		src = *save_ptr;

	if (*src == '\0')
	{
		*save_ptr = src;
		src = NULL;
		*res = src;
		return 1;
	}
	/* Find the end of the token.  */
	int len = strcspn(src, delim);
	end = src + len;
	if (*end == '\0')
	{
		*save_ptr = end;
		*res = src;
		src = NULL;
		return 1;
	}

	/* Terminate the token and make *SAVE_PTR point past it.  */
	*end = '\0';
	*save_ptr = end + 1;
	*res = src;
	src = NULL;
	return 0;
}

int split(char *src, const char *delim, char **dest, int max_field_num)
{
	if (src == nullptr || strlen(src) == 0) return 0;
	if (delim == nullptr || strlen(delim) == 0) return 0;
	if (dest == nullptr) return 0;

	int count = 0;
	char *next = nullptr, *saveptr = nullptr;;

	int ret = strtok_a(src, dest, delim, &saveptr);
	++dest;
	++count;
	while (ret != 1)
	{
		ret = strtok_a(nullptr, dest, delim, &saveptr);
		++dest;
		++count;
		if (count > max_field_num) return -1;
	}

	return count;
}

int main()
{
	std::string line = ",,,";
	char* arr[10];
	int nsplit = split(const_cast<char*>(line.c_str()), ",", arr, 4);
	std::cout << nsplit << std::endl;
	for (int i = 0; i < nsplit; ++i)
		if (arr[i] != NULL) std::cout << arr[i] << std::endl;
		else std::cout << "empty\n";
	return 0;
}
