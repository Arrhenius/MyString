#ifndef MYSTRING_H
#define MYSTRING_H


class MyString
{
public:
	MyString();
	MyString(const char* pszString);
	~MyString();
	void	reverse();
	void	append(const char* pszString);
	void	toUpperCase();
	void	toLowerCase();
	int		getSize();
	char*	getString() const;
	char*	subString(int beginIndex, int endIndex);

private:
	int		size;
	char*	string;
};

#endif // MYSTRING_H
