/* menu system definitions. */

#ifndef MENU_DEFS_H
#define MENU_DEFS_H
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <curses.h>

#define MSG_XLAT(x) msg_string(x)
#define DYNAMIC_MENUS
#define MENU_EXPANDS

typedef struct menudesc menudesc;
typedef struct menu_ent menu_ent;
struct menu_ent {
	const char	*opt_name;
	const char	*opt_exp_name;
	short		opt_menu;
	short		opt_flags;
	int		(*opt_action)(menudesc *, void *);
};

#define OPT_NOMENU	0
#define OPT_SUB	1
#define OPT_ENDWIN	2
#define OPT_EXIT	4
#define OPT_IGNORE	8
#define OPT_NOSHORT	16

struct menudesc {
	const char	*title;
	const char	*exp_title;
	short		y, x;
	short		h, w;
	short		mopt;
	short		numopts;
	short		cursel;
	short		topline;
	menu_ent	*opts;
	WINDOW		*mw;
	WINDOW		*sv_mw;
	const char	*helpstr;
	const char	*exitstr;
	void		(*expand_act)(menudesc *, void *);
	void		(*post_act)(menudesc *, void *);
	void		(*exit_act)(menudesc *, void *);
	void		(*draw_line)(menudesc *, int, void *);
};

/* defines for mopt field. */
#define MC_NOEXITOPT 0x001
#define MC_NOBOX 0x002
#define MC_SCROLL 0x004
#define MC_NOSHORTCUT 0x008
#define MC_NOCLEAR 0x010
#define MC_DFLTEXIT 0x020
#define MC_ALWAYS_SCROLL 0x040
#define MC_SUBMENU 0x080
#define MC_CONTINUOUS 0x100
#define MC_VALID 0x200

/* Prototypes */
int menu_init(void);
void process_menu(int, void *);
__dead void __menu_initerror(void);
int new_menu(const char *, menu_ent *, int, 
	int, int, int, int, int,
	void (*)(menudesc *, void *), void (*)(menudesc *, int, void *),
	void (*)(menudesc *, void *), const char *, const char *);
void free_menu(int);
void set_menu_numopts(int, int);
menudesc *get_menudesc(int);

/* Menu names */
#define MENU_mountoptions	1
#define MENU_netbsd	2
#define MENU_utility	3
#define MENU_colors	4
#define MENU_yesno	5
#define MENU_noyes	6
#define MENU_ok	7
#define MENU_sizechoice	8
#define MENU_ptnsize_replace_existing_partition	9
#define MENU_distmedium	10
#define MENU_distset	11
#define MENU_ftpsource	12
#define MENU_nfssource	13
#define MENU_fdremount	14
#define MENU_fdok	15
#define MENU_fd_type	16
#define MENU_floppysource	17
#define MENU_cdromsource	18
#define MENU_localfssource	19
#define MENU_localdirsource	20
#define MENU_namesrv6	21
#define MENU_rootsh	22
#define MENU_zeroconf	23
#define MENU_binpkg	24
#define MENU_pkgsrc	25
#define MENU_usersh	26
#define MENU_convertscheme	27
#define MENU_reedit	28
#define MENU_pmdiskentry	29
#define MENU_shred_modes	30
#define MENU_pmpartentry	31
#define MENU_raidlevel	32
#define MENU_cgd_enctype	33
#define MENU_cgd_ivtype	34
#define MENU_cgd_keygentype	35
#define MENU_cgd_verifytype	36
#define MENU_not_enough_entropy	37
#define MENU_entropy_select_file	38
#define MENU_entropy_nfssource	39
#define MENU_entropy_ftpsource	40
#define MENU_entropy_localfs	41
#define MENU_getboottype	42
#define MENU_consolebaud	43
#define MENU_biosonematch	44
#define MENU_biosmultmatch	45

#define DYN_MENU_START	46
#define MAX_STRLEN 40
#endif
