/*	$Id$	*/
/*
 * Copyright(C) Caldera International Inc. 2001-2002. All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * Redistributions of source code and documentation must retain the above
 * copyright notice, this list of conditions and the following disclaimer.
 * Redistributions in binary form must reproduce the above copyright
 * notice, this list of conditionsand the following disclaimer in the
 * documentation and/or other materials provided with the distribution.
 * All advertising materials mentioning features or use of this software
 * must display the following acknowledgement:
 * 	This product includes software developed or owned by Caldera
 *	International, Inc.
 * Neither the name of Caldera International, Inc. nor the names of other
 * contributors may be used to endorse or promote products derived from
 * this software without specific prior written permission.
 *
 * USE OF THE SOFTWARE PROVIDED FOR UNDER THIS LICENSE BY CALDERA
 * INTERNATIONAL, INC. AND CONTRIBUTORS ``AS IS'' AND ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED.  IN NO EVENT SHALL CALDERA INTERNATIONAL, INC. BE LIABLE
 * FOR ANY DIRECT, INDIRECT INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OFLIABILITY, WHETHER IN CONTRACT,
 * STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING
 * IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE 
 * POSSIBILITY OF SUCH DAMAGE.
 */

# include "pass2.h"

# define WPTR TPTRTO|TINT|TFLOAT|TDOUBLE|TPOINT|TUNSIGNED
# define AWD SNAME|SOREG|SCON|STARNM|STARREG
/* tbl */
# define TANYSIGNED TINT|TSHORT|TCHAR
# define TANYUSIGNED TPOINT|TUNSIGNED|TUSHORT|TUCHAR
# define TANYFIXED TANYSIGNED|TANYUSIGNED
# define TWORD TINT|TUNSIGNED|TPOINT
/* tbl */
# define TLL TLONGLONG|TULONGLONG
# define TBREG TLONGLONG|TULONGLONG|TDOUBLE

struct optab  table[] = {
/* First entry must be an empty entry */
{ -1, FOREFF, SANY, TANY, SANY, TANY, 0, 0, "", },

{ PCONV,	INAREG|INAREG,
	SAREG|AWD,	TCHAR|TSHORT,
	SANY,	TPOINT,
		NAREG|NASL,	RESC1,
		"	cvtZLl	AL,A1\n", },

{ PCONV,	INAREG|INAREG,
	SAREG|AWD,	TUCHAR|TUSHORT,
	SANY,	TPOINT,
		NAREG|NASL,	RESC1,
		"	movzZLl	AL,A1\n", },

/* Handle conversions in C code */
{ SCONV,	INAREG|INBREG|FORCC,
	SAREG|SBREG|AWD,	TANY,
	SANY,		TANY,
		NBREG|NBSL,	RESC1|RESCC,
		"ZG", },

{ GOTO,	FOREFF,
	SCON,	TANY,
	SANY,	TANY,
		0,	RNOP,
		"	ZJ\n", },

{ GOTO,	FOREFF,
	SAREG,	TANY,
	SANY,	TANY,
		0,	RNOP,
		"	jmp	(AL)\n", },

{ STARG,	FOREFF,
	SCON|SAREG,	TANY,
	SANY,	TANY,
		NSPECIAL,	RNOP,
		"ZS", },

#if 0
{ STASG,	FORARG,
	SNAME|SOREG,	TANY,
	SCON|SAREG,	TANY,
		0,	RNULL,
		"	subl2	ZT,sp\nZS", },
#endif

{ ADDROF,	INAREG,
	SNAME,	TANY,
	SAREG,	TANY,
		NAREG,	RESC1,
		"	movab	AL,A1\n", },

{ STASG,	FOREFF,
	SNAME|SOREG,	TANY,
	SCON|SAREG,	TANY,
		0,	RNOP,
		"ZS", },

{ STASG,	INAREG,
	SNAME|SOREG,	TANY,
	SCON,	TANY,
		NAREG,	RDEST,
		"ZS	movl	AR,A1\n", },

{ STASG,	INAREG,
	SNAME|SOREG,	TANY,
	SAREG,	TANY,
		0,	RDEST,
		"	pushl	AR\nZS	movl	(sp)+,AR\n", },

{ FLD,	INAREG|INAREG,
	SANY,	TANY,
	SFLD,	TANYSIGNED,
		NAREG|NASR,	RESC1,
		"	extv	H,S,AR,A1\n", },

{ FLD,	INAREG|INAREG,
	SANY,	TANY,
	SFLD,	TANYUSIGNED,
		NAREG|NASR,	RESC1,
		"	extzv	H,S,AR,A1\n", },

#if 0
{ FLD,	FORARG,
	SANY,	TANY,
	SFLD,	ANYSIGNED,
		0,	RNULL,
		"	extv	H,S,AR,-(sp)\n", },

{ FLD,	FORARG,
	SANY,	TANY,
	SFLD,	ANYUSIGNED,
		0,	RNULL,
		"	extzv	H,S,AR,-(sp)\n", },
#endif

{ OPLOG,	FORCC,
	SBREG|AWD,	TLONGLONG|TULONGLONG,
	SBREG,		TLONGLONG|TULONGLONG,
		0,	0,
		"ZB", },


{ OPLOG,	FORCC,
	SAREG|AWD,	TWORD,
	SAREG|AWD,	TWORD,
		0,	RESCC,
		"	cmpl	AL,AR\n", },

{ OPLOG,	FORCC,
	SAREG|AWD,	TSHORT|TUSHORT,
	SAREG|AWD,	TSHORT|TUSHORT,
		0,	RESCC,
		"	cmpw	AL,AR\n", },

{ OPLOG,	FORCC,
	SAREG|AWD,	TCHAR|TUCHAR,
	SAREG|AWD,	TCHAR|TUCHAR,
		0,	RESCC,
		"	cmpb	AL,AR\n", },

{ OPLOG,	FORCC,
	SAREG|AWD,	TSHORT|TUSHORT,
	SSCON,	TANY,
		0,	RESCC,
		"	cmpw	AL,AR\n", },

{ OPLOG,	FORCC,
	SAREG|AWD,	TCHAR|TUCHAR,
	SCCON,	TANY,
		0,	RESCC,
		"	cmpb	AL,AR\n", },

{ OPLOG,	FORCC,
	SAREG|AWD,	TDOUBLE,
	SAREG|AWD,	TDOUBLE,
		0,	RESCC,
		"	cmpd	AL,AR\n", },

{ OPLOG,	FORCC,
	SAREG|AWD,	TFLOAT|TDOUBLE,
	SAREG|AWD,	TFLOAT|TDOUBLE,
		0,	RESCC,
		"	cmpf	AL,AR\n", },

{ CCODES,	INAREG|INAREG,
	SANY,	TANY,
	SANY,	TANY,
		NAREG,	RESC1,
		"	movl	$1,A1\nZN", },

/*
 * Subroutine calls.
 */

{ CALL,		FOREFF,
	SCON,	TANY,
	SANY,	TANY,
		0,	0,
		"	calls	ZC,CL\n", },

{ UCALL,	FOREFF,
	SCON,	TANY,
	SANY,	TANY,
		0,	0,
		"	calls	$0,CL\n", },

{ CALL,		INAREG,
	SCON,	TANY,
	SANY,	TANY,
		NAREG|NASL,	RESC1, /* should be register 0 */
		"	calls	ZC,CL\n", },

{ UCALL,	INAREG,
	SCON,	TANY,
	SANY,	TANY,
		NAREG|NASL,	RESC1, /* should be register 0 */
		"	calls	$0,CL\n", },

{ CALL,		FOREFF,
	SAREG,	TANY,
	SANY,	TANY,
		0,	0,	/* should be 0 */
		"	calls	ZC,(AL)\n", },

{ CALL,		INAREG,
	SAREG,	TANY,
	SANY,	TANY,
		NAREG|NASL,	RESC1,	/* should be 0 */
		"	calls	ZC,(AL)\n", },

{ UCALL,	FOREFF,
	SAREG,	TANY,
	SANY,	TWORD|TCHAR|TUCHAR|TSHORT|TUSHORT|TFLOAT|TDOUBLE,
		0,	0,	/* should be 0 */
		"	calls	ZC,(AL)\n", },

{ UCALL,	INAREG,
	SAREG,	TANY,
	SANY,	TWORD|TCHAR|TUCHAR|TSHORT|TUSHORT|TFLOAT|TDOUBLE,
		NAREG|NASL,	RESC1,	/* should be 0 */
		"	calls	ZC,(AL)\n", },

{ UCALL,	FOREFF,
	SNAME,	TANY,
	SANY,	TANY,
		0,	0,	/* really reg 0 */
		"	calls	ZC,*AL\n", },

{ UCALL,	INAREG,
	SNAME,	TANY,
	SANY,	TANY,
		NAREG|NASL,	RESC1,	/* really reg 0 */
		"	calls	ZC,*AL\n", },

{ UCALL,	FOREFF,
	SSOREG,	TANY,
	SANY,	TANY,
		0,	0,	/* really reg 0 */
		"	calls	ZC,*AL\n", },

{ UCALL,	INAREG,
	SSOREG,	TANY,
	SANY,	TANY,
		NAREG|NASL,	RESC1,	/* really reg 0 */
		"	calls	ZC,*AL\n", },

{ STCALL,	INAREG,
	SCON,	TANY,
	SANY,	TANY,
		NAREG|NASL,	RESC1, /* should be register 0 */
		"	calls	ZC,CL\n", },



/*
 * Function arguments
 */
{ FUNARG,	FOREFF,
	SCON|SAREG|SNAME|SOREG,	TWORD|TPOINT,
	SANY,	TWORD|TPOINT,
		0,	RNULL,
		"	pushl AL\n" },

{ FUNARG,	FOREFF,
	SCON|SBREG|SNAME|SOREG,	TLL,
	SANY,	TANY,
		0,	RNULL,
		"	movq AL,-(%sp)\n" },

#if 0
{ ASG RS,	INAREG|FOREFF|FORCC,
	SAREG,	TWORD,
	SCON,	TINT,
		0,	RLEFT|RESCC,
		"	extzv	AR,ZU,AL,AL\n", },

{ ASG RS,	INAREG|FOREFF|FORCC,
	SAREG,	TWORD,
	SAREG,	ANYFIXED,
		NAREG,	RLEFT|RESCC,
		"	subl3	AR,$32,A1\n	extzv	AR,A1,AL,AL\n", },

{ ASG RS,	INAREG|FOREFF|FORCC,
	SAREG,	TWORD,
	SAREG|AWD,	TWORD,
		NAREG,	RLEFT|RESCC,
		"	subl3	AR,$32,A1\n	extzv	AR,A1,AL,AL\n", },
#endif

{ RS,	INAREG|INAREG|FORCC,
	SAREG,	TWORD,
	SCON,	TINT,
		NAREG|NASL,	RESC1|RESCC,
		"	extzv	AR,ZU,AL,A1\n", },

#if 0
{ ASG LS,	INAREG|FOREFF|FORCC,
	SAREG|AWD,	TWORD,
	SAREG|AWD,	ANYSIGNED|ANYUSIGNED,
		0,	RLEFT|RESCC,
		"	ashl	AR,AL,AL\n", },
#endif

{ LS,	INBREG|FORCC,
	SBREG|AWD,	TLL,
	SAREG|SBREG|AWD,	TANY,
		NBREG|NBSL|NBSR,	RESC1|RESCC,
		"	ashq	AR,AL,A1\n", },

{ LS,	INAREG|INAREG|FORCC,
	SAREG|AWD,	TWORD,
	SAREG|AWD,	TANYSIGNED|TANYUSIGNED,
		NAREG|NASL|NASR,	RESC1|RESCC,
		"	ashl	AR,AL,A1\n", },

#if 0
{ INCR,	FOREFF,
	SAREG|AWD,	TANY,
	SANY,	TANY,
		0,	RLEFT,
		"	ZE\n", },

{ DECR,	FOREFF,
	SAREG|AWD,	TANY,
	SCON,	TANY,
		0,	RLEFT,
		"	ZE\n", },

{ INCR,	INAREG|INAREG,
	SAREG|AWD,	TANY,
	SCON,	TANY,
		NAREG,	RESC1,
		"	ZD\n", },

{ DECR,	INAREG|INAREG,
	SAREG|AWD,	TANY,
	SCON,	TANY,
		NAREG,	RESC1,
		"	ZD\n", },
#endif

/* Have FOREFF first to catch mem-mem moves */
{ ASSIGN,	FOREFF,
	SBREG|AWD,	TBREG,
	SBREG|AWD,	TBREG,
		0,	0,
		"	movq	AR,AL\n", },

{ ASSIGN,	INBREG,
	SBREG,	TBREG,
	SBREG|AWD,	TBREG,
		0,	RDEST,
		"	movq	AR,AL\n", },

{ ASSIGN,	INBREG,
	SBREG|AWD,	TBREG,
	SBREG,	TBREG,
		0,	RDEST,
		"	movq	AR,AL\n", },

{ ASSIGN,	FOREFF,
	SBREG|AWD,	TBREG,
	SBREG|AWD,	TBREG,
		0,	0,
		"	movq	AR,AL\n", },

{ ASSIGN,	INAREG|FOREFF|FORCC,
	SAREG|AWD,	TANY,
	SAREG|AWD,	TANY,
		0,	RDEST|RESCC,
		"	ZA\n", },

{ ASSIGN,	INAREG|FOREFF|FORCC,
	SFLD,	TANY,
	SAREG|AWD,	TWORD,
		0,	RDEST|RESCC,
		"	insv	AR,H,S,AL\n", },

{ ASSIGN,	INAREG|FOREFF|FORCC,
	SAREG|AWD,	TWORD,
	SFLD,	TANYSIGNED,
		0,	RDEST|RESCC,
		"	extv	H,S,AR,AL\n", },

{ ASSIGN,	INAREG|FOREFF|FORCC,
	SAREG|AWD,	TWORD,
	SFLD,	TANYUSIGNED,
		0,	RDEST|RESCC,
		"	extzv	H,S,AR,AL\n", },

/* dummy UNARY MUL entry to get U* to possibly match OPLTYPE */
{ UMUL,	FOREFF,
	SCC,	TANY,
	SCC,	TANY,
		0,	RNULL,
		"	HELP HELP HELP\n", },

{ UMUL, INBREG,
	SANY,	TPOINT|TLL,
	SOREG,	TPOINT|TLL,
		NBREG|NBSL,	RESC1,
		"	movq AL,A1\n", },

{ UMUL, INAREG,
	SANY,	TPOINT|TWORD,
	SOREG,	TPOINT|TWORD,
		NAREG|NASL,	RESC1,
		"	movl AL,A1\n", },

{ UMUL, INAREG,
	SANY,	TPOINT|TSHORT|TUSHORT,
	SOREG,	TPOINT|TSHORT|TUSHORT,
		NAREG|NASL,	RESC1,
		"	movw AL,A1\n", },

{ UMUL, INAREG,
	SANY,	TPOINT|TCHAR|TUCHAR,
	SOREG,	TPOINT|TCHAR|TUCHAR,
		NAREG|NASL,	RESC1,
		"	movb AL,A1\n", },

#if 0
{ REG,	FORARG,
	SANY,	TANY,
	SAREG,	TDOUBLE|TFLOAT,
		0,	RNULL,
		"	movZR	AR,-(sp)\n", },

{ REG,	INTEMP,
	SANY,	TANY,
	SAREG,	TDOUBLE,
		2*NTEMP,	RESC1,
		"	movd	AR,A1\n", },

{ REG,	INTEMP,
	SANY,	TANY,
	SAREG,	TANY,
		NTEMP,	RESC1,
		"	movZF	AR,A1\n", },
#endif

{ OPLEAF,	FOREFF,
	SANY,	TANY,
	SAREG|AWD,	TANY,
		0,	RLEFT,
		"", },

{ OPLTYPE,	INBREG,
	SANY,	TANY,
	SCON|SOREG|SNAME,	TLONGLONG|TULONGLONG,
		NBREG,	RESC1,
		"	movq AL,A1\n", },

{ OPLTYPE,	INAREG|INAREG,
	SANY,	TANY,
	SANY,	TFLOAT|TDOUBLE,
		2*NAREG|NASR,	RESC1,
		"	ZA\n", },

{ OPLTYPE,	INAREG|INAREG,
	SANY,	TANY,
	SANY,	TANY,
		NAREG|NASR,	RESC1,
		"	ZA\n", },

{ OPLTYPE,	FORCC,
	SANY,	TANY,
	SANY,	TANY,
		0,	RESCC,
		"	tstZR	AR\n", },

#if 0
{ OPLTYPE,	FORARG,
	SANY,	TANY,
	SANY,	TWORD,
		0,	RNULL,
		"	pushl	AR\n", },

{ OPLTYPE,	FORARG,
	SANY,	TANY,
	SANY,	TCHAR|TSHORT,
		0,	RNULL,
		"	cvtZRl	AR,-(sp)\n", },

{ OPLTYPE,	FORARG,
	SANY,	TANY,
	SANY,	TUCHAR|TUSHORT,
		0,	RNULL,
		"	movzZRl	AR,-(sp)\n", },

{ OPLTYPE,	FORARG,
	SANY,	TANY,
	SANY,	TDOUBLE,
		0,	RNULL,
		"	movd	AR,-(sp)\n", },

{ OPLTYPE,	FORARG,
	SANY,	TANY,
	SANY,	TFLOAT,
		0,	RNULL,
		"	cvtfd	AR,-(sp)\n", },
#endif

{ UMINUS,	INAREG|FORCC,
	SAREG|AWD,	TINT|TUNSIGNED|TLONG|TULONG|TDOUBLE,
	SANY,	TANY,
		NAREG|NASL,	RESC1|RESCC,
		"	mnegZL	AL,A1\n", },

{ COMPL,	INAREG|FORCC,
	SAREG|AWD,	TINT|TUNSIGNED,
	SANY,	TANY,
		NAREG|NASL,	RESC1|RESCC,
		"	mcomZL	AL,A1\n", },

{ COMPL,	INAREG|FORCC,
	SAREG|AWD,	TANYSIGNED|TANYUSIGNED,
	SANY,	TANY,
		NAREG|NASL,	RESC1|RESCC,
		"	cvtZLl	AL,A1\n	mcoml	A1,A1\n", },

{ AND,	FORCC,
	SAREG|AWD,	TWORD,
	SCON,	TWORD,
		0,	RESCC,
		"	bitl	ZZ,AL\n", },

{ AND,	FORCC,
	SAREG|AWD,	TSHORT|TUSHORT,
	SSCON,	TWORD,
		0,	RESCC,
		"	bitw	ZZ,AL\n", },

{ AND,	FORCC,
	SAREG|AWD,	TCHAR|TUCHAR,
	SCCON,	TWORD,
		0,	RESCC,
		"	bitb	ZZ,AL\n", },

#if 0
{ ASG AND,	INAREG|FOREFF|FORCC,
	SAREG,	ANYFIXED,
	SCON,	TWORD,
		0,	RLEFT|RESCC,
		"	bicl2	AR,AL\n", },

{ ASG OPMUL,	INAREG|FOREFF|FORCC,
	SAREG|AWD,	TINT|TUNSIGNED|TLONG|TULONG,
	SAREG|AWD,	TINT|TUNSIGNED|TLONG|TULONG,
		0,	RLEFT|RESCC,
		"	OL2	AR,AL\n", },
#endif

{ OPMUL,	INAREG|INAREG|FORCC,
	SAREG,	TINT|TUNSIGNED|TLONG|TULONG,
	SAREG|AWD,	TINT|TUNSIGNED|TLONG|TULONG,
		0,	RLEFT|RESCC,
		"	OL2	AR,AL\n", },

{ OPMUL,	INAREG|INAREG|FORCC,
	SAREG|AWD,	TINT|TUNSIGNED|TLONG|TULONG,
	SAREG|AWD,	TINT|TUNSIGNED|TLONG|TULONG,
		NAREG|NASL|NASR,	RESC1|RESCC,
		"	OL3	AR,AL,A1\n", },

#if 0
{ ASG MOD,	INAREG|INAREG|FOREFF|FORCC,
	SAREG,	TINT|TUNSIGNED|TLONG|TULONG,
	SAREG|AWD,	TINT|TUNSIGNED|TLONG|TULONG,
		NAREG,	RLEFT|RESCC,
		"	divl3	AR,AL,A1\n	mull2	AR,A1\n	subl2	A1,AL\n", },
#endif

{ MOD,	INAREG|INAREG,
	SAREG|AWD,	TINT|TUNSIGNED|TLONG|TULONG,
	SAREG|AWD,	TINT|TUNSIGNED|TLONG|TULONG,
		NAREG,	RESC1,
		"	divl3	AR,AL,A1\n	mull2	AR,A1\n	subl3	A1,AL,A1\n", },

#if 0
{ ASG PLUS,	INAREG|FOREFF|FORCC,
	SAREG|AWD,	ANYSIGNED|ANYUSIGNED,
	SONE,	TINT|TLONG,
		0,	RLEFT|RESCC,
		"	incZL	AL\n", },

{ ASG MINUS,	INAREG|FOREFF|FORCC,
	SAREG|AWD,	ANYSIGNED|ANYUSIGNED,
	SONE,	TINT|TLONG,
		0,	RLEFT|RESCC,
		"	decZL	AL\n", },
#endif

{ PLUS,	INBREG|FORCC,
	SBREG|AWD,	TLL,
	SBREG|AWD,	TLL,
		NBREG|NBSL|NBSR,	RESC1|RESCC,
		"	movq	AL,A1\n"
		"	addl2	AR,A1\n"
		"	adwc	UR,U1\n", },

{ PLUS,	INAREG|INAREG|FORCC,
	SAREG,	TANYFIXED,
	SONE,	TWORD,
		0,	RLEFT|RESCC,
		"	incZL	AL\n", },

{ MINUS,	INAREG|INAREG|FORCC,
	SAREG,	TANYFIXED,
	SONE,	TWORD,
		0,	RLEFT|RESCC,
		"	decZL	AL\n", },

{ MINUS,	INBREG|FORCC,
	SBREG|AWD,	TLL,
	SBREG|AWD,	TLL,
		NBREG|NBSL|NBSR,	RESC1|RESCC,
		"	movq	AL,A1\n"
		"	subl2	AR,A1\n"
		"	sbwc	UR,U1\n", },

#if 0
{ ASG OPSIMP,	INAREG|FOREFF|FORCC,
	SAREG|AWD,	TWORD,
	SAREG|AWD,	TWORD,
		0,	RLEFT|RESCC,
		"	OL2	AR,AL\n", },

{ ASG OPSIMP,	INAREG|FOREFF|FORCC,
	AWD,	TSHORT|TUSHORT,
	SAREG|AWD,	TSHORT|TUSHORT,
		0,	RLEFT|RESCC,
		"	OW2	AR,AL\n", },

{ ASG OPSIMP,	INAREG|FOREFF|FORCC,
	AWD,	TSHORT|TUSHORT,
	SSCON,	TWORD,
		0,	RLEFT|RESCC,
		"	OW2	AR,AL\n", },

{ ASG OPSIMP,	INAREG|FOREFF|FORCC,
	AWD,	TCHAR|TUCHAR,
	SAREG|AWD,	TCHAR|TUCHAR,
		0,	RLEFT|RESCC,
		"	OB2	AR,AL\n", },

{ ASG OPSIMP,	INAREG|FOREFF|FORCC,
	AWD,	TCHAR|TUCHAR,
	SCCON,	TWORD,
		0,	RLEFT|RESCC,
		"	OB2	AR,AL\n", },
#endif

{ DIV,	INBREG,
	SBREG|AWD, 	TLL,
	SBREG|AWD, 	TLL,
		NSPECIAL|NBREG|NBSL|NBSR,	RESC1,
		"ZO", },

{ MOD,	INBREG,
	SBREG|AWD, 	TLL,
	SBREG|AWD, 	TLL,
		NSPECIAL|NBREG|NBSL|NBSR,	RESC1,
		"ZO", },

{ MUL,	INBREG,
	SBREG|AWD, 	TLL,
	SBREG|AWD, 	TLL,
		NSPECIAL|NBREG|NBSL|NBSR,	RESC1,
		"ZO", },

{ OPSIMP,	INAREG|INAREG|FORCC,
	SAREG,	TANYFIXED,
	SAREG|AWD,	TWORD,
		0,	RLEFT|RESCC,
		"	OL2	AR,AL\n", },

{ OPSIMP,	INAREG|INAREG|FORCC,
	SAREG|AWD,	TWORD,
	SAREG|AWD,	TWORD,
		NAREG|NASL|NASR,	RESC1|RESCC,
		"	OL3	AR,AL,A1\n", },

#if 0
{ ASG OPFLOAT,	INAREG|FOREFF|FORCC,
	SAREG|AWD,	TDOUBLE,
	SAREG|AWD,	TDOUBLE,
		0,	RLEFT|RESCC,
		"	OD2	AR,AL\n", },

{ ASG OPFLOAT,	INAREG|FOREFF|FORCC,
	SAREG|AWD,	TFLOAT,
	SAREG|AWD,	TFLOAT,
		0,	RLEFT|RESCC,
		"	OF2	AR,AL\n", },

{ ASG OPFLOAT,	INAREG|FOREFF|FORCC,
	SAREG|AWD,	TDOUBLE,
	SAREG|AWD,	TFLOAT,
		NAREG|NASR,	RLEFT|RESCC,
		"	cvtfd	AR,A1\n	OD2	A1,AL\n", },

{ ASG OPFLOAT,	INAREG|INAREG|FOREFF|FORCC,
	SAREG|AWD,	TFLOAT,
	SAREG|AWD,	TDOUBLE,
		NAREG,	RLEFT|RESC1|RESCC,
		"	cvtfd	AL,A1\n	OD2	AR,A1\n	cvtdf	A1,AL\n", },
#endif

{ OPFLOAT,	INAREG|INAREG|FORCC,
	SAREG,	TDOUBLE,
	SAREG|AWD,	TDOUBLE,
		0,	RLEFT|RESCC,
		"	OD2	AR,AL\n", },

{ OPFLOAT,	INAREG|INAREG|FORCC,
	SAREG|AWD,	TDOUBLE,
	SAREG|AWD,	TDOUBLE,
		NAREG|NASL|NASR,	RESC1|RESCC,
		"	OD3	AR,AL,A1\n", },

{ OPFLOAT,	INAREG|INAREG|FORCC,
	SAREG|AWD,	TFLOAT,
	SAREG|AWD,	TDOUBLE,
		NAREG|NASL,	RESC1|RESCC,
		"	cvtfd	AL,A1\n	OD2	AR,A1\n", },

{ OPFLOAT,	INAREG|INAREG|FORCC,
	SAREG|AWD,	TDOUBLE,
	SAREG|AWD,	TFLOAT,
		NAREG|NASR,	RESC1|RESCC,
		"	cvtfd	AR,A1\n	OD3	A1,AL,A1\n", },

{ OPFLOAT,	INAREG|INAREG|FORCC,
	SAREG|AWD,	TFLOAT,
	SAREG|AWD,	TFLOAT,
		NAREG|NASL|NASR,	RESC1|RESCC,
		"	OF3	AR,AL,A1\n	cvtfd	A1,A1\n", },

	/* Default actions for hard trees ... */

# define DF(x) FORREW,SANY,TANY,SANY,TANY,REWRITE,x,""

{ UMUL, DF( UMUL ), },

{ ASSIGN, DF(ASSIGN), },

{ STASG, DF(STASG), },

{ OPLEAF, DF(NAME), },

{ OPLOG,	FORCC,
	SANY,	TANY,
	SANY,	TANY,
		REWRITE,	BITYPE,
		"", },

{ OPUNARY, DF(UMINUS), },

{ OPANY, DF(BITYPE), },

{ FREE,	FREE,	FREE,	FREE,	FREE,	FREE,	FREE,	FREE,	"help; I'm in trouble\n" }
};
