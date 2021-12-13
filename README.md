# c_pgm_calling_dbl_pgm<br />
**Created Date:** 9/15/2011<br />
**Last Updated:** 9/15/2011<br />
**Description:** This is an example of calling a C routine from Synergy and calling a Synergy routine from C on the VMS operating system.<br />
**Platforms:** OpenVMS<br />
**Products:** Synergy DBL<br />
**Minimum Version:** 6<br />
**Author:** Galen Carpenter
<hr>

**Additional Information:**
There are three files:
test.dbl This is the mainline Synergy source
sub1.c This is the C source
sub2.dbl This is the Synergy subroutine and function
To compile:
cc sub1
dbl sub2
dbl test
To link:
dblink test,sub1,sub2
