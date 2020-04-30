/**
 *  Ledmatrix Aplication Program Interface
 *  Written By  : Septian D. Chandra
 *  E-mail      : septian.d.chandra@gmail.com
 *  Blog URL    : http://solderingcodes.blogspot.com
 */

#ifndef _PRG_CONF_H_
#define _PRG_CONF_H_

#define DIR_STR(x)				#x
#define PROG_DEF_DIR(x)			DIR_STR(program/x/prg_def.h)
#define BOARD_DEF_DIR(x)		DIR_STR(board/x.h)

/*--------- Define Program & Board name here ---------*/	
#define PROG_DEF_H				PROG_DEF_DIR(pakwahyu_v2)	
#define BOARD_DEF_H             BOARD_DEF_DIR(brd_DMD19)
/*----------------------------------------------------*/				

#endif	/* _PRG_CONF_H_ */
