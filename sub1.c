#include <stdio.h>
#include <memory.h>

#define ALPHA_TYPE	0x0e	/* Type value for an alpha descriptor	*/
#define DECIMAL_TYPE	0x14	/* Type value for an decimal descriptor	*/

typedef struct descrip		/* Structure template for a descriptor	*/
{			/* Note: array descriptors are more complex	*/
    unsigned short len;			/* Length of the data		*/
    unsigned char type;			/* Type of the data		*/
    unsigned char clas;			/* Class of the data		*/
    char *addr;				/* Address of the data		*/
} DESCRIP;

			/* Setup template for routines being called	*/
extern int sub2(DESCRIP *, DESCRIP *, int);
extern int fun2(DESCRIP *, DESCRIP *, int);

/*
 *	The SUB1 subroutine has three arguments.  The first and second
 *	arguments is passed by descriptor.  The third argument is passed
 *	by value.
 *
 *	This subroutine takes the first argument which is alpha and adds
 *	the text " from sub1" to the end of the passed text and passes
 *	that to the Synergy subroutine SUB2 along with the second and
 *	third arguments.
 */
int
sub1(DESCRIP *arg1, DESCRIP *arg2, int arg3)
{
    DESCRIP newarg1;		/* New descriptor passed to SUB2	*/
    int val;			/* Value returned from SUB2		*/
    char buf[32];		/* Buffer for first argument to SUB2	*/

			/* Display the three arguments as passed in	*/
    printf("sub1: arg1 = %08X -> %02X %02X %04X %08X\n", arg1, arg1->clas, arg1->type, arg1->len, arg1->addr);
    printf("sub1: arg2 = %08X -> %02X %02X %04X %08X\n", arg2, arg2->clas, arg2->type, arg2->len, arg2->addr);
    printf("sub1: arg3 = %d\n", arg3);
			/* The buf array above is 32 bytes long		*/
			/* Ten bytes are going to be added to the end	*/
			/*  of the contents of arg1 so issue a warning	*/
			/*  if the passed in argument is too long as	*/
			/*  the buffer would then overflow.		*/
    if (arg1->len > 20)
	printf("sub1: Warning: arg1 too long\n");
			/* Copy the contents of arg1 to buf		*/
    memcpy(buf, arg1->addr, arg1->len);
    buf[arg1->len] = '\0';		/* Null terminate the string	*/
    printf("sub1: arg1 = %s\n", buf);	/* Display the arg1 contents	*/
    printf("\n");	/* Output \n so sub2 will not overwrite it	*/
			/* Add " from sub1" to the end of buf		*/
    strcpy(buf + arg1->len, " from sub1");
			/* Setup a new descriptor for this new argument	*/
    newarg1.clas = 1;			/* Set the class to 1		*/
    newarg1.type = ALPHA_TYPE;		/* Set the type to ALPHA	*/
    newarg1.len = strlen(buf);		/* Set the descriptor length	*/
    newarg1.addr = buf;			/* Set the address to be buf	*/
			/* Now call the Synergy routine SUB2		*/
			/* It is setup like a ^val function with three	*/
			/* arguments: alpha text, decimal value, and	*/
			/* the third argument is passed by value	*/
    val = sub2(&newarg1, arg2, arg3);
    printf("sub1: val = %d\n\n", val);	/* Display the returned value	*/
			/* Now call the Synergy routine FUN2		*/
			/* It is setup as a ^val function with three	*/
			/* arguments: alpha text, decimal value, and	*/
			/* the third argument is passed by value	*/
    val = fun2(&newarg1, arg2, arg3);
    printf("sub1: val = %d\n\n", val);	/* Display the returned value	*/
    return(val);		/* Return the value to the caller	*/
}
