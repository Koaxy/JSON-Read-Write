#include "KoaxyUtils.h"

int main()
{
	KoaxyJSON::WriteValue("NameThisWhatever", "WrittenData");
	KoaxyJSON::ReadValue("NameThisWhatever", 0); // Check the ReadValue Implement, you need to specify a type, as a BOOL, INT or STRING.
}
