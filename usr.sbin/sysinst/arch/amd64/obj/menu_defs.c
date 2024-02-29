#include "menu_defs.h"


#include <stdio.h>
#include <time.h>
#include <curses.h>
#include "defs.h"
#include "md.h"
#include "msg_defs.h"
#include "menu_defs.h"

static menudesc menu_def[];

static void
expand_option_text(menudesc *menu, void *arg, int sel)
{
	arg_replace *ar = arg;
	struct menu_ent *opt = &menu->opts[sel];

	if (menu->opts[sel].opt_exp_name)
		return;	/* has already been expanded */

	opt->opt_exp_name =
	    str_arg_subst(MSG_XLAT(opt->opt_name), ar->argc, ar->argv);
}

void
expand_all_option_texts(menudesc *menu, void *arg)
{
	arg_replace *ar = arg;
	const char *title;
	int i;

	if (menu->title != NULL && menu->exp_title == NULL) {
		title = MSG_XLAT(menu->title);
		if (needs_expanding(title, ar->argc)) {
			menu->exp_title = str_arg_subst(title,
			    ar->argc, ar->argv);
		}
	}
	for (i = 0; i < menu->numopts; i++) {
		const char *t = MSG_XLAT(menu->opts[i].opt_name);

		if (t == NULL) continue;

		if (needs_expanding(t, ar->argc))
			expand_option_text(menu, arg, i);
	}
}

/*
 * Re-create the menu window with heigh/width updated to current state.
 */
void
resize_menu_height(menudesc *m)
{

	if (m->mw == NULL)
		return;

	wclear(m->mw);
	if (m->sv_mw) {
		overwrite(m->sv_mw, m->mw);
		delwin(m->sv_mw);
		m->sv_mw = NULL;
	}
	wnoutrefresh(m->mw);
	delwin(m->mw);	 
	m->mw = NULL;
}

static void
src_legend(menudesc *menu, const char *legend, const char *text)
{
        wprintw(menu->mw, "%-35s %.50s", MSG_XLAT(legend), MSG_XLAT(text));
}

static void
src_prompt(const char *prompt, char *buf, size_t size)
{
	msg_prompt_win(prompt, -1, 12, 0, 0, buf, buf, size);
}

static void
remove_sub_menu(int menuID)
{

	for (size_t i = 0; i < DYN_MENU_START; i++) {
		for (int j = 0; j < menu_def[i].numopts; j++) {
			if ((menu_def[i].opts[j].opt_flags & OPT_SUB)
			    && menu_def[i].opts[j].opt_menu == menuID) {

				for (int k = j + 1; k < menu_def[i].numopts;
				    k++) {
					menu_def[i].opts[k-1] =
					    menu_def[i].opts[k];
				}
				menu_def[i].numopts--;
				return;

			}
		}
	}
}

#ifndef NO_PARTMAN
static void
remove_menu_option(int menuID, const char *option)
{

	for (int j = 0; j < menu_def[menuID].numopts; j++) {
		if (menu_def[menuID].opts[j].opt_name == option) {
			for (int k = j + 1; k < menu_def[menuID].numopts;
			    k++) {
				menu_def[menuID].opts[k-1] =
				    menu_def[menuID].opts[k];
			}
			menu_def[menuID].numopts--;
			return;

		}
	}
}
#endif

void
remove_color_options()
{
	/*
	 * Current terminal type does not support colors, so remove all
	 * menu entries (actually that is: Utils/Color Scheme) that do not
	 * make any sense in this case.
	 */
	remove_sub_menu(MENU_colors);
}

#ifndef NO_PARTMAN
void
remove_raid_options()
{
	/*
	 * No raidframe available, remove the following menu entries:
	 */
	remove_menu_option(MENU_pmdiskentry, MSG_fmtasraid);
	remove_menu_option(MENU_pmpartentry, MSG_fmtasraid);
}

void
remove_lvm_options()
{
	/*
	 * No LVM available, remove the following menu entries:
	 */
	remove_menu_option(MENU_pmdiskentry, MSG_fmtaslvm);
	remove_menu_option(MENU_pmpartentry, MSG_fmtaslvm);
}

void
remove_cgd_options()
{
	/*
	 * No CGD available, remove the following menu entries:
	 */
	remove_menu_option(MENU_pmdiskentry, MSG_encrypt);
	remove_menu_option(MENU_pmpartentry, MSG_encrypt);
}
#endif



/*ARGSUSED*/
static int opt_act_1_0(menudesc *m, void *arg)
{
	 struct single_part_fs_edit *edit = arg;
		  edit->pset->infos[edit->index].mountflags ^= PUIMNT_LOG; 
	return 1;
}

/*ARGSUSED*/
static int opt_act_1_1(menudesc *m, void *arg)
{
	 struct single_part_fs_edit *edit = arg;
		  edit->pset->infos[edit->index].mountflags ^= PUIMNT_ASYNC; 
	return 1;
}

/*ARGSUSED*/
static int opt_act_1_2(menudesc *m, void *arg)
{
	 struct single_part_fs_edit *edit = arg;
		  edit->pset->infos[edit->index].mountflags ^= PUIMNT_NOATIME; 
	return 1;
}

/*ARGSUSED*/
static int opt_act_1_3(menudesc *m, void *arg)
{
	 struct single_part_fs_edit *edit = arg;
		  edit->pset->infos[edit->index].mountflags ^= PUIMNT_NODEV; 
	return 1;
}

/*ARGSUSED*/
static int opt_act_1_4(menudesc *m, void *arg)
{
	 struct single_part_fs_edit *edit = arg;
		  edit->pset->infos[edit->index].mountflags ^= PUIMNT_NODEVMTIME; 
	return 1;
}

/*ARGSUSED*/
static int opt_act_1_5(menudesc *m, void *arg)
{
	 struct single_part_fs_edit *edit = arg;
		  edit->pset->infos[edit->index].mountflags ^= PUIMNT_NOEXEC; 
	return 1;
}

/*ARGSUSED*/
static int opt_act_1_6(menudesc *m, void *arg)
{
	 struct single_part_fs_edit *edit = arg;
		  edit->pset->infos[edit->index].mountflags ^= PUIMNT_NOSUID; 
	return 1;
}

/*ARGSUSED*/
static int opt_act_1_7(menudesc *m, void *arg)
{
	 struct single_part_fs_edit *edit = arg;
		  edit->pset->infos[edit->index].mountflags ^= PUIMNT_NOAUTO; 
	return 1;
}

/*ARGSUSED*/
static void menu_2_postact(menudesc *menu, void *arg)
{
	 toplevel(); 
}

/*ARGSUSED*/
static int opt_act_2_0(menudesc *m, void *arg)
{
	 do_install(); 
	return 0;
}

/*ARGSUSED*/
static int opt_act_2_1(menudesc *m, void *arg)
{
	 do_upgrade(); 
	return 0;
}

/*ARGSUSED*/
static int opt_act_2_2(menudesc *m, void *arg)
{
	 do_reinstall_sets(); 
	return 0;
}

/*ARGSUSED*/
static int opt_act_2_3(menudesc *m, void *arg)
{
	 system("/sbin/reboot -q"); 
	return 1;
}

/*ARGSUSED*/
static int opt_act_2_5(menudesc *m, void *arg)
{
	 do_configmenu(NULL); 
	return 0;
}

/*ARGSUSED*/
static void menu_3_postact(menudesc *menu, void *arg)
{
	 toplevel(); 
}

/*ARGSUSED*/
static int opt_act_3_0(menudesc *m, void *arg)
{
	 system("/bin/sh -i -E"); 
	return 0;
}

/*ARGSUSED*/
static int opt_act_3_1(menudesc *m, void *arg)
{
	 set_timezone(); 
	return 0;
}

/*ARGSUSED*/
static int opt_act_3_2(menudesc *m, void *arg)
{
	
			extern int network_up;
			network_up = 0;
			config_network(1);
		
	return 0;
}

/*ARGSUSED*/
static int opt_act_3_3(menudesc *m, void *arg)
{
	
#ifndef NO_PARTMAN
			partman_go = 1;
			partman(NULL);
#endif
		
	return 0;
}

/*ARGSUSED*/
static int opt_act_3_4(menudesc *m, void *arg)
{
	 do_logging(); 
	return 0;
}

/*ARGSUSED*/
static int opt_act_3_6(menudesc *m, void *arg)
{
	 system("/sbin/halt -q"); 
	return 1;
}

/*ARGSUSED*/
static int opt_act_4_0(menudesc *m, void *arg)
{
	 do_coloring(COLOR_WHITE,COLOR_BLACK); 
	return 0;
}

/*ARGSUSED*/
static int opt_act_4_1(menudesc *m, void *arg)
{
	 do_coloring(COLOR_BLACK,COLOR_WHITE); 
	return 0;
}

/*ARGSUSED*/
static int opt_act_4_2(menudesc *m, void *arg)
{
	 do_coloring(COLOR_WHITE,COLOR_BLUE); 
	return 0;
}

/*ARGSUSED*/
static int opt_act_4_3(menudesc *m, void *arg)
{
	 do_coloring(COLOR_GREEN,COLOR_BLACK); 
	return 0;
}

/*ARGSUSED*/
static void menu_5_postact(menudesc *menu, void *arg)
{
	 arg_rv *p = arg;
		menu->title = p->arg ? p->arg : MSG_yes_or_no; 
}

/*ARGSUSED*/
static int opt_act_5_0(menudesc *m, void *arg)
{
	 ((arg_rv*)arg)->rv = 1; 
	return 1;
}

/*ARGSUSED*/
static int opt_act_5_1(menudesc *m, void *arg)
{
	 ((arg_rv*)arg)->rv = 0; 
	return 1;
}

/*ARGSUSED*/
static void menu_6_postact(menudesc *menu, void *arg)
{
	 arg_rv *p = arg;
		menu->title = p->arg ? p->arg : MSG_yes_or_no; 
}

/*ARGSUSED*/
static int opt_act_6_0(menudesc *m, void *arg)
{
	 ((arg_rv*)arg)->rv = 0; 
	return 1;
}

/*ARGSUSED*/
static int opt_act_6_1(menudesc *m, void *arg)
{
	 ((arg_rv*)arg)->rv = 1; 
	return 1;
}

/*ARGSUSED*/
static void menu_7_postact(menudesc *menu, void *arg)
{
	 menu->title = arg; 
}

/*ARGSUSED*/
static void menu_8_postact(menudesc *menu, void *arg)
{
	
		if (sizemult == pm->current_cylsize)
			menu->cursel = 2;
		else if (sizemult == 1)
			menu->cursel = 3;
		else if (sizemult == (GIG/pm->sectorsize))
			menu->cursel = 0;
		else
			menu->cursel = 1; 
}

/*ARGSUSED*/
static int opt_act_8_0(menudesc *m, void *arg)
{
	 set_sizemult(GIG, pm->sectorsize); 
	return 1;
}

/*ARGSUSED*/
static int opt_act_8_1(menudesc *m, void *arg)
{
	 set_sizemult(MEG, pm->sectorsize); 
	return 1;
}

/*ARGSUSED*/
static int opt_act_8_2(menudesc *m, void *arg)
{
	 set_sizemult(pm->current_cylsize*pm->sectorsize, pm->sectorsize); 
	return 1;
}

/*ARGSUSED*/
static int opt_act_8_3(menudesc *m, void *arg)
{
	 set_sizemult(pm->sectorsize, pm->sectorsize); 
	return 1;
}

/*ARGSUSED*/
static void menu_9_postact(menudesc *menu, void *arg)
{
	 menu->cursel = 1; 
}

/*ARGSUSED*/
static int opt_act_9_0(menudesc *m, void *arg)
{
	 *((int*)arg) = 1; 
	return 1;
}

/*ARGSUSED*/
static int opt_act_9_1(menudesc *m, void *arg)
{
	 *((int*)arg) = 0; 
	return 1;
}

/*ARGSUSED*/
static int opt_act_10_0(menudesc *m, void *arg)
{
	 *(int *)arg = get_via_cdrom(); 
	return 1;
}

/*ARGSUSED*/
static int opt_act_10_1(menudesc *m, void *arg)
{
	 *(int *)arg = get_via_ftp(XFER_HTTP); 
	return 1;
}

/*ARGSUSED*/
static int opt_act_10_2(menudesc *m, void *arg)
{
	 *(int *)arg = get_via_ftp(XFER_FTP); 
	return 1;
}

/*ARGSUSED*/
static int opt_act_10_3(menudesc *m, void *arg)
{
	 *(int *)arg = get_via_nfs(); 
	return 1;
}

/*ARGSUSED*/
static int opt_act_10_4(menudesc *m, void *arg)
{
	 *(int *)arg = get_via_floppy(); 
	return 1;
}

/*ARGSUSED*/
static int opt_act_10_5(menudesc *m, void *arg)
{
	 *(int *)arg = get_via_localfs(); 
	return 1;
}

/*ARGSUSED*/
static int opt_act_10_6(menudesc *m, void *arg)
{
	 *(int *)arg = get_via_localdir();
	return 1;
}

/*ARGSUSED*/
static int opt_act_10_7(menudesc *m, void *arg)
{
	 *(int *)arg = SET_SKIP; 
	return 1;
}

/*ARGSUSED*/
static int opt_act_10_8(menudesc *m, void *arg)
{
	 *(int *)arg = SET_SKIP_GROUP; 
	return 1;
}

/*ARGSUSED*/
static int opt_act_10_9(menudesc *m, void *arg)
{
	 *(int *)arg = SET_ABANDON; 
	return 1;
}

/*ARGSUSED*/
static void menu_11_postact(menudesc *menu, void *arg)
{
	 msg_display (MSG_distset); 
}

/*ARGSUSED*/
static int opt_act_11_0(menudesc *m, void *arg)
{
	 *(int *)arg = 1; init_set_status(0);  
	return 1;
}

/*ARGSUSED*/
static int opt_act_11_1(menudesc *m, void *arg)
{
	 *(int *)arg = 1; init_set_status(SFLAG_NOX); 
	return 1;
}

/*ARGSUSED*/
static int opt_act_11_2(menudesc *m, void *arg)
{
	 *(int *)arg = 1; init_set_status(SFLAG_MINIMAL); 
	return 1;
}

/*ARGSUSED*/
static int opt_act_11_3(menudesc *m, void *arg)
{
	 *(int *)arg = 1; init_set_status(SFLAG_MINIMAL); customise_sets(); 
	return 1;
}

/*ARGSUSED*/
static void menu_12_postact(menudesc *menu, void *arg)
{
	
		msg_display_subst(MSG_ftpsource, 2, "." SETS_TAR_SUFF,
		    url_proto((uintptr_t)((arg_rv*)arg)->arg));
	    
}

/*ARGSUSED*/
static int opt_act_12_0(menudesc *m, void *arg)
{
	 src_prompt(MSG_Host, ftp.xfer_host[
		XFER_HOST((uintptr_t)((arg_rv*)arg)->arg)],
		sizeof ftp.xfer_host[XFER_HOST(
		(uintptr_t)((arg_rv*)arg)->arg)]); 
	return 0;
}

/*ARGSUSED*/
static int opt_act_12_1(menudesc *m, void *arg)
{
	 src_prompt(MSG_Base_dir, ftp.dir, sizeof ftp.dir); 
	return 0;
}

/*ARGSUSED*/
static int opt_act_12_2(menudesc *m, void *arg)
{
	 src_prompt(MSG_Set_dir_bin, set_dir_bin, sizeof set_dir_bin); 
	return 0;
}

/*ARGSUSED*/
static int opt_act_12_3(menudesc *m, void *arg)
{
	 src_prompt(MSG_Set_dir_src, set_dir_src, sizeof set_dir_src); 
	return 0;
}

/*ARGSUSED*/
static int opt_act_12_4(menudesc *m, void *arg)
{
	 src_prompt(MSG_Dist_postfix, dist_postfix, sizeof dist_postfix); 
	return 0;
}

/*ARGSUSED*/
static int opt_act_12_5(menudesc *m, void *arg)
{
	 src_prompt(MSG_User, ftp.user, sizeof ftp.user);
			ftp.pass[0] = 0;
		
	return 0;
}

/*ARGSUSED*/
static int opt_act_12_6(menudesc *m, void *arg)
{
	 if (strcmp(ftp.user, "ftp") == 0)
			src_prompt(MSG_email, ftp.pass, sizeof ftp.pass);
		  else {
			msg_prompt_noecho(MSG_Password, "",
					ftp.pass, sizeof ftp.pass);
		  }
		
	return 0;
}

/*ARGSUSED*/
static int opt_act_12_7(menudesc *m, void *arg)
{
	 src_prompt(MSG_Proxy, ftp.proxy, sizeof ftp.proxy);
		  if (strcmp(ftp.proxy, "") == 0) {
			unsetenv("ftp_proxy");
			unsetenv("http_proxy");
		  } else {
			setenv("ftp_proxy", ftp.proxy, 1);
			setenv("http_proxy", ftp.proxy, 1);
		  }
		
	return 0;
}

/*ARGSUSED*/
static int opt_act_12_8(menudesc *m, void *arg)
{
	 src_prompt(MSG_Xfer_dir, xfer_dir, sizeof xfer_dir); 
	return 0;
}

/*ARGSUSED*/
static int opt_act_12_9(menudesc *m, void *arg)
{
	clean_xfer_dir = ask_yesno(MSG_delete_xfer_file); 
	return 0;
}

/*ARGSUSED*/
static int opt_act_12_10(menudesc *m, void *arg)
{
	
			extern int network_up;
			network_up = 0;
			config_network(1);
		
	return 0;
}

/*ARGSUSED*/
static int opt_act_12_11(menudesc *m, void *arg)
{
	 ((arg_rv*)arg)->rv = SET_RETRY; 
	return 1;
}

/*ARGSUSED*/
static void menu_13_postact(menudesc *menu, void *arg)
{
	 const char suff[] = "." SETS_TAR_SUFF;
		msg_display_subst(MSG_nfssource, 1, &suff); 
}

/*ARGSUSED*/
static int opt_act_13_0(menudesc *m, void *arg)
{
	 src_prompt(MSG_Host, nfs_host, sizeof nfs_host); 
	return 0;
}

/*ARGSUSED*/
static int opt_act_13_1(menudesc *m, void *arg)
{
	 src_prompt(MSG_Base_dir, nfs_dir, sizeof nfs_dir); 
	return 0;
}

/*ARGSUSED*/
static int opt_act_13_2(menudesc *m, void *arg)
{
	 src_prompt(MSG_Set_dir_bin, set_dir_bin, sizeof set_dir_bin); 
	return 0;
}

/*ARGSUSED*/
static int opt_act_13_3(menudesc *m, void *arg)
{
	 src_prompt(MSG_Set_dir_src, set_dir_src, sizeof set_dir_src); 
	return 0;
}

/*ARGSUSED*/
static int opt_act_13_4(menudesc *m, void *arg)
{
	 src_prompt(MSG_Dist_postfix, dist_postfix, sizeof dist_postfix); 
	return 0;
}

/*ARGSUSED*/
static int opt_act_13_5(menudesc *m, void *arg)
{
	
			extern int network_up;
			network_up = 0;
			config_network(1);
		
	return 0;
}

/*ARGSUSED*/
static int opt_act_13_6(menudesc *m, void *arg)
{
	 *((int*)arg) = SET_RETRY; 
	return 1;
}

/*ARGSUSED*/
static int opt_act_14_0(menudesc *m, void *arg)
{
	 *(int *)arg = SET_CONTINUE; 
	return 1;
}

/*ARGSUSED*/
static int opt_act_14_1(menudesc *m, void *arg)
{
	 *(int *)arg = SET_OK; 
	return 1;
}

/*ARGSUSED*/
static int opt_act_14_2(menudesc *m, void *arg)
{
	 *(int *)arg = SET_RETRY; 
	return 1;
}

/*ARGSUSED*/
static int opt_act_15_0(menudesc *m, void *arg)
{
	 *(int *)arg = SET_CONTINUE; 
	return 1;
}

/*ARGSUSED*/
static int opt_act_15_1(menudesc *m, void *arg)
{
	 *(int *)arg = SET_OK; 
	return 1;
}

/*ARGSUSED*/
static int opt_act_15_2(menudesc *m, void *arg)
{
	 *(int *)arg = SET_RETRY; 
	return 1;
}

/*ARGSUSED*/
static int opt_act_16_0(menudesc *m, void *arg)
{
	 fd_type = "msdos"; 
	return 1;
}

/*ARGSUSED*/
static int opt_act_16_1(menudesc *m, void *arg)
{
	 fd_type = "ffs"; 
	return 1;
}

/*ARGSUSED*/
static void menu_17_postact(menudesc *menu, void *arg)
{
	 msg_display(MSG_floppysource); 
}

/*ARGSUSED*/
static int opt_act_17_0(menudesc *m, void *arg)
{
	 src_prompt(MSG_dev, fd_dev, sizeof fd_dev); 
	return 0;
}

/*ARGSUSED*/
static int opt_act_17_2(menudesc *m, void *arg)
{
	 src_prompt(MSG_Xfer_dir, xfer_dir, sizeof xfer_dir); 
	return 0;
}

/*ARGSUSED*/
static int opt_act_17_3(menudesc *m, void *arg)
{
	clean_xfer_dir = ask_yesno(MSG_delete_xfer_file); 
	return 0;
}

/*ARGSUSED*/
static int opt_act_17_4(menudesc *m, void *arg)
{
	 *((int*)arg) = SET_RETRY; 
	return 1;
}

/*ARGSUSED*/
static void menu_18_postact(menudesc *menu, void *arg)
{
	 const char suff[] = "." SETS_TAR_SUFF;
		msg_display_add_subst(MSG_cdromsource, 1, &suff); 
}

/*ARGSUSED*/
static int opt_act_18_0(menudesc *m, void *arg)
{
	 src_prompt(MSG_dev, cdrom_dev, sizeof cdrom_dev); 
	return 0;
}

/*ARGSUSED*/
static int opt_act_18_1(menudesc *m, void *arg)
{
	 src_prompt(MSG_Set_dir_bin, set_dir_bin, sizeof set_dir_bin); 
	return 0;
}

/*ARGSUSED*/
static int opt_act_18_2(menudesc *m, void *arg)
{
	 src_prompt(MSG_Set_dir_src, set_dir_src, sizeof set_dir_src); 
	return 0;
}

/*ARGSUSED*/
static int opt_act_18_3(menudesc *m, void *arg)
{
	 src_prompt(MSG_Dist_postfix, dist_postfix, sizeof dist_postfix); 
	return 0;
}

/*ARGSUSED*/
static int opt_act_18_4(menudesc *m, void *arg)
{
	 *((int*)arg) = SET_ABANDON; 
	return 1;
}

/*ARGSUSED*/
static int opt_act_18_5(menudesc *m, void *arg)
{
	 *((int*)arg) = SET_RETRY; 
	return 1;
}

/*ARGSUSED*/
static void menu_19_postact(menudesc *menu, void *arg)
{
	 const char suff[] = "." SETS_TAR_SUFF;
		msg_display_subst(MSG_localfssource, 1, &suff); 
}

/*ARGSUSED*/
static int opt_act_19_0(menudesc *m, void *arg)
{
	 src_prompt(MSG_dev, localfs_dev, sizeof localfs_dev);
	return 0;
}

/*ARGSUSED*/
static int opt_act_19_1(menudesc *m, void *arg)
{
	 src_prompt(MSG_filesys, localfs_fs, sizeof localfs_fs); 
	return 0;
}

/*ARGSUSED*/
static int opt_act_19_2(menudesc *m, void *arg)
{
	 src_prompt(MSG_Base_dir, localfs_dir, sizeof localfs_dir);
	return 0;
}

/*ARGSUSED*/
static int opt_act_19_3(menudesc *m, void *arg)
{
	 src_prompt(MSG_Set_dir_bin, set_dir_bin, sizeof set_dir_bin); 
	return 0;
}

/*ARGSUSED*/
static int opt_act_19_4(menudesc *m, void *arg)
{
	 src_prompt(MSG_Set_dir_src, set_dir_src, sizeof set_dir_src); 
	return 0;
}

/*ARGSUSED*/
static int opt_act_19_5(menudesc *m, void *arg)
{
	 src_prompt(MSG_Dist_postfix, dist_postfix, sizeof dist_postfix); 
	return 0;
}

/*ARGSUSED*/
static int opt_act_19_6(menudesc *m, void *arg)
{
	 *((int*)arg) = SET_RETRY; 
	return 1;
}

/*ARGSUSED*/
static void menu_20_postact(menudesc *menu, void *arg)
{
	 const char suff[] = "." SETS_TAR_SUFF;
		msg_display_subst(MSG_localdir, 1, &suff); 
}

/*ARGSUSED*/
static int opt_act_20_0(menudesc *m, void *arg)
{
	 src_prompt(MSG_Base_dir, localfs_dir, 60); 
	return 0;
}

/*ARGSUSED*/
static int opt_act_20_1(menudesc *m, void *arg)
{
	 src_prompt(MSG_Set_dir_bin, set_dir_bin, 60); 
	return 0;
}

/*ARGSUSED*/
static int opt_act_20_2(menudesc *m, void *arg)
{
	 src_prompt(MSG_Set_dir_src, set_dir_src, 60); 
	return 0;
}

/*ARGSUSED*/
static int opt_act_20_3(menudesc *m, void *arg)
{
	 src_prompt(MSG_Dist_postfix, dist_postfix, 60); 
	return 0;
}

/*ARGSUSED*/
static int opt_act_20_4(menudesc *m, void *arg)
{
	 *((int*)arg) = SET_RETRY; 
	return 1;
}

/*ARGSUSED*/
static int opt_act_21_0(menudesc *m, void *arg)
{
	
#ifdef INET6
		  strlcpy(net_namesvr, "8.8.8.8",
		      sizeof(net_namesvr));
		  *((int*)arg) = 1;
#else
		  *((int*)arg) = 0;
#endif
		
	return 1;
}

/*ARGSUSED*/
static int opt_act_21_1(menudesc *m, void *arg)
{
	
#ifdef INET6
		  strlcpy(net_namesvr, "8.8.4.4",
		      sizeof(net_namesvr));
		  *((int*)arg) = 1;
#else
		  *((int*)arg) = 0;
#endif
		
	return 1;
}

/*ARGSUSED*/
static int opt_act_21_2(menudesc *m, void *arg)
{
	
#ifdef INET6
		  strlcpy(net_namesvr, "2001:4860:4860::8888",
		      sizeof(net_namesvr));
		  *((int*)arg) = 1;
#else
		  *((int*)arg) = 0;
#endif
		
	return 1;
}

/*ARGSUSED*/
static int opt_act_21_3(menudesc *m, void *arg)
{
	
#ifdef INET6
		  strlcpy(net_namesvr, "2001:4860:4860::8844",
		      sizeof(net_namesvr));
		  *((int*)arg) = 1;
#else
		  *((int*)arg) = 0;
#endif
		
	return 1;
}

/*ARGSUSED*/
static int opt_act_21_4(menudesc *m, void *arg)
{
	 *((int*)arg) = 0; 
	return 1;
}

/*ARGSUSED*/
static int opt_act_22_0(menudesc *m, void *arg)
{
	*(const char **)arg = "/bin/sh";
	return 1;
}

/*ARGSUSED*/
static int opt_act_22_1(menudesc *m, void *arg)
{
	*(const char **)arg = "/bin/ksh";
	return 1;
}

/*ARGSUSED*/
static int opt_act_22_2(menudesc *m, void *arg)
{
	*(const char **)arg = "/bin/csh";
	return 1;
}

/*ARGSUSED*/
static int opt_act_23_0(menudesc *m, void *arg)
{
	*(const char **)arg = "mdnsd";
	return 1;
}

/*ARGSUSED*/
static int opt_act_23_1(menudesc *m, void *arg)
{
	*(const char **) arg = "mdnsd+nsswitch";
	return 1;
}

/*ARGSUSED*/
static int opt_act_23_2(menudesc *m, void *arg)
{
	*(const char **)arg = "No";
	return 1;
}

/*ARGSUSED*/
static void menu_24_postact(menudesc *menu, void *arg)
{
	 msg_display(MSG_pkgpath); 
}

/*ARGSUSED*/
static int opt_act_24_0(menudesc *m, void *arg)
{
	 src_prompt(MSG_Host,
		pkg.xfer_host[XFER_HOST(pkg.xfer)],
		sizeof pkg.xfer_host[XFER_HOST(pkg.xfer)]); 
	return 0;
}

/*ARGSUSED*/
static int opt_act_24_1(menudesc *m, void *arg)
{
	 src_prompt(MSG_Base_dir, pkg.dir, sizeof pkg.dir); 
	return 0;
}

/*ARGSUSED*/
static int opt_act_24_2(menudesc *m, void *arg)
{
	 src_prompt(MSG_Pkg_dir, pkg_dir, sizeof pkg_dir); 
	return 0;
}

/*ARGSUSED*/
static int opt_act_24_3(menudesc *m, void *arg)
{
	 src_prompt(MSG_User, pkg.user, sizeof pkg.user);
			pkg.pass[0] = 0;
		
	return 0;
}

/*ARGSUSED*/
static int opt_act_24_4(menudesc *m, void *arg)
{
	 if (strcmp(pkg.user, "ftp") == 0)
			src_prompt(MSG_email, pkg.pass, sizeof pkg.pass);
		  else {
			msg_prompt_noecho(MSG_Password, "",
					pkg.pass, sizeof pkg.pass);
		  }
		
	return 0;
}

/*ARGSUSED*/
static int opt_act_24_5(menudesc *m, void *arg)
{
	 src_prompt(MSG_Proxy, pkg.proxy, sizeof pkg.proxy);
		  if (strcmp(pkg.proxy, "") == 0) {
			unsetenv("ftp_proxy");
			unsetenv("http_proxy");
		  } else {
			setenv("ftp_proxy", pkg.proxy, 1);
			setenv("http_proxy", pkg.proxy, 1);
		  }
		
	return 0;
}

/*ARGSUSED*/
static int opt_act_24_6(menudesc *m, void *arg)
{
	 src_prompt("Additional packages", (char*)(((arg_rv*)arg)->arg),
			 sizeof(char) * STRSIZE); 
	return 0;
}

/*ARGSUSED*/
static int opt_act_24_7(menudesc *m, void *arg)
{
	
			extern int network_up;
			network_up = 0;
			config_network(1);
			mnt_net_config();
		
	return 0;
}

/*ARGSUSED*/
static int opt_act_24_8(menudesc *m, void *arg)
{
	 pkg.xfer = (pkg.xfer+1) % (XFER_MAX+1); 
	return 0;
}

/*ARGSUSED*/
static int opt_act_24_9(menudesc *m, void *arg)
{
	 ((arg_rv*)arg)->rv = SET_SKIP; 
	return 1;
}

/*ARGSUSED*/
static void menu_25_postact(menudesc *menu, void *arg)
{
	 msg_display(MSG_pkgsrc); 
}

/*ARGSUSED*/
static int opt_act_25_0(menudesc *m, void *arg)
{
	 src_prompt(MSG_Host,
			pkgsrc.xfer_host[XFER_HOST(pkgsrc.xfer)],
			sizeof pkgsrc.xfer_host[XFER_HOST(pkgsrc.xfer)]); 
	return 0;
}

/*ARGSUSED*/
static int opt_act_25_1(menudesc *m, void *arg)
{
	 src_prompt(MSG_Pkgsrc_dir, pkgsrc_dir, sizeof pkgsrc_dir); 
	return 0;
}

/*ARGSUSED*/
static int opt_act_25_2(menudesc *m, void *arg)
{
	 src_prompt(MSG_User, pkgsrc.user, sizeof pkgsrc.user);
			pkgsrc.pass[0] = 0;
		
	return 0;
}

/*ARGSUSED*/
static int opt_act_25_3(menudesc *m, void *arg)
{
	 if (strcmp(pkgsrc.user, "ftp") == 0)
			src_prompt(MSG_email, pkgsrc.pass, sizeof pkgsrc.pass);
		  else {
			msg_prompt_noecho(MSG_Password, "",
					pkgsrc.pass, sizeof pkgsrc.pass);
		  }
		
	return 0;
}

/*ARGSUSED*/
static int opt_act_25_4(menudesc *m, void *arg)
{
	 src_prompt(MSG_Proxy, pkgsrc.proxy, sizeof pkgsrc.proxy);
		  if (strcmp(pkgsrc.proxy, "") == 0) {
			unsetenv("ftp_proxy");
			unsetenv("http_proxy");
		  } else {
			setenv("ftp_proxy", pkgsrc.proxy, 1);
			setenv("http_proxy", pkgsrc.proxy, 1);
		  }
		
	return 0;
}

/*ARGSUSED*/
static int opt_act_25_5(menudesc *m, void *arg)
{
	 src_prompt(MSG_Xfer_dir, xfer_dir, sizeof xfer_dir); 
	return 0;
}

/*ARGSUSED*/
static int opt_act_25_6(menudesc *m, void *arg)
{
	clean_xfer_dir = ask_yesno(MSG_delete_xfer_file); 
	return 0;
}

/*ARGSUSED*/
static int opt_act_25_7(menudesc *m, void *arg)
{
	 pkgsrc.xfer = (pkgsrc.xfer+1) % (XFER_MAX+1); 
	return 0;
}

/*ARGSUSED*/
static int opt_act_25_8(menudesc *m, void *arg)
{
	 *((int*)arg) = SET_SKIP;
	return 1;
}

/*ARGSUSED*/
static int opt_act_26_0(menudesc *m, void *arg)
{
	 ushell = "/bin/sh";
	return 1;
}

/*ARGSUSED*/
static int opt_act_26_1(menudesc *m, void *arg)
{
	 ushell = "/bin/ksh";
	return 1;
}

/*ARGSUSED*/
static int opt_act_26_2(menudesc *m, void *arg)
{
	 ushell = "/bin/csh";
	return 1;
}

/*ARGSUSED*/
static int opt_act_27_0(menudesc *m, void *arg)
{
	 *(int*)arg = 0; 
	return 1;
}

/*ARGSUSED*/
static int opt_act_27_1(menudesc *m, void *arg)
{
	 *(int*)arg = 1; 
	return 1;
}

/*ARGSUSED*/
static int opt_act_27_2(menudesc *m, void *arg)
{
	 *(int*)arg = 2; 
	return 1;
}

/*ARGSUSED*/
static int opt_act_27_3(menudesc *m, void *arg)
{
	 *(int*)arg = 3; 
	return 1;
}

/*ARGSUSED*/
static void menu_28_expact(menudesc *menu, void *arg)
{
	 expand_all_option_texts(menu, arg); 
}

/*ARGSUSED*/
static int opt_act_28_0(menudesc *m, void *arg)
{
	((arg_rep_int*)arg)->rv = 1;
	return 1;
}

/*ARGSUSED*/
static int opt_act_28_1(menudesc *m, void *arg)
{
	((arg_rep_int*)arg)->rv = 2;
	return 1;
}

/*ARGSUSED*/
static int opt_act_28_2(menudesc *m, void *arg)
{
	((arg_rep_int*)arg)->rv = 0;
	return 1;
}

/*ARGSUSED*/
static void menu_29_postact(menudesc *menu, void *arg)
{
	 pmdiskentry_enable(menu, arg); 
}

/*ARGSUSED*/
static int opt_act_29_0(menudesc *m, void *arg)
{
	 pm_edit_partitions(arg); 
	return 1;
}

/*ARGSUSED*/
static int opt_act_29_1(menudesc *m, void *arg)
{
	
		struct pm_devs *my_pm = pm_from_pe(arg);
		const char *err;

		if (!convert_scheme(my_pm, false, &err))
			err_msg_win(err);
		else
			pm_partusage(my_pm, -1, 1);
	
	return 1;
}

/*ARGSUSED*/
static int opt_act_29_2(menudesc *m, void *arg)
{
	
		pm_whole_disk(arg, SY_NEWRAID);
	
	return 1;
}

/*ARGSUSED*/
static int opt_act_29_3(menudesc *m, void *arg)
{
	
		part_id new_part;

		new_part = pm_whole_disk(arg, SY_NEWLVM);
		if (new_part != NO_PART)
			pm_set_lvmpv(pm_from_pe(arg), new_part, true);
	
	return 1;
}

/*ARGSUSED*/
static int opt_act_29_4(menudesc *m, void *arg)
{
	
		part_id new_part;
		new_part = pm_whole_disk(arg, SY_NEWCGD);
		if (new_part != NO_PART)
			 pm_cgd_edit_new(pm_from_pe(arg), new_part);
	
	return 1;
}

/*ARGSUSED*/
static int opt_act_29_6(menudesc *m, void *arg)
{
	
				/* label_read(); */ pm->unsaved = 0;
				pm_partusage(pm, -1, 1);
	
	return 1;
}

/*ARGSUSED*/
static int opt_act_29_7(menudesc *m, void *arg)
{
	
				if (pm_unconfigure(pm) == 0)
					pm_partusage(pm, -1, 1);
	
	return 1;
}

/*ARGSUSED*/
static int opt_act_30_0(menudesc *m, void *arg)
{
	 pm_shred(arg, SHRED_ZEROS); 
	return 1;
}

/*ARGSUSED*/
static int opt_act_30_1(menudesc *m, void *arg)
{
	 pm_shred(arg, SHRED_RANDOM); 
	return 1;
}

/*ARGSUSED*/
static int opt_act_31_0(menudesc *m, void *arg)
{
	
		struct part_entry *cur_pe = arg;
		pm->unsaved = 1;
		pm_editpart(cur_pe->id);
		pm_partusage(pm, cur_pe->id, 1);
	
	return 1;
}

/*ARGSUSED*/
static int opt_act_31_1(menudesc *m, void *arg)
{
	
		if (pm->no_part) {
			hit_enter_to_continue(NULL, MSG_notsupported);
			return -1;
		}
		struct part_entry *cur_pe = arg;
		pm->unsaved = 1;
		pm_partusage(pm, cur_pe->id, 1);
		pm_setfstype(pm, cur_pe->id, FS_RAID, 0);
	
	return 1;
}

/*ARGSUSED*/
static int opt_act_31_2(menudesc *m, void *arg)
{
	
		if (pm->no_part) {
			hit_enter_to_continue(NULL, MSG_notsupported);
			return -1;
		}
		struct part_entry *cur_pe = arg;
		pm->unsaved = 1;
		pm_partusage(pm, cur_pe->id, 1);
		pm_setfstype(pm, cur_pe->id, FS_BSDFFS, 2);
		pm_set_lvmpv(pm, cur_pe->id, true);
	
	return 1;
}

/*ARGSUSED*/
static int opt_act_31_3(menudesc *m, void *arg)
{
	
		if (pm->no_part) {
			hit_enter_to_continue(NULL, MSG_notsupported);
			return -1;
		}
		struct part_entry *cur_pe = arg;
		pm->unsaved = 1;
		pm_partusage(pm, cur_pe->id, 1);
		pm_setfstype(pm, cur_pe->id, FS_CGD, 0);
		pm_cgd_edit_old(cur_pe);
	
	return 1;
}

/*ARGSUSED*/
static int opt_act_31_5(menudesc *m, void *arg)
{
	
		struct part_entry *cur_pe = arg;
		pm_umount(pm, cur_pe->id);
	
	return 1;
}

/*ARGSUSED*/
static int opt_act_31_6(menudesc *m, void *arg)
{
	
		struct part_entry *cur_pe = arg;
		pm->unsaved = 1;
		pm_partusage(pm, cur_pe->id, 1);
		if (pm->no_part)
			pm_unconfigure(pm);
		else
			pm_setfstype(pm, cur_pe->id, FS_UNUSED, 0);
	
	return 1;
}

/*ARGSUSED*/
static int opt_act_32_0(menudesc *m, void *arg)
{
	 *(int *)arg = 0; 
	return 1;
}

/*ARGSUSED*/
static int opt_act_32_1(menudesc *m, void *arg)
{
	 *(int *)arg = 1; 
	return 1;
}

/*ARGSUSED*/
static int opt_act_32_2(menudesc *m, void *arg)
{
	 *(int *)arg = 4; 
	return 1;
}

/*ARGSUSED*/
static int opt_act_32_3(menudesc *m, void *arg)
{
	 *(int *)arg = 5; 
	return 1;
}

/*ARGSUSED*/
static int opt_act_33_0(menudesc *m, void *arg)
{
	 *(const char**)arg = "aes-xts"; 
	return 1;
}

/*ARGSUSED*/
static int opt_act_33_1(menudesc *m, void *arg)
{
	 *(const char**)arg = "aes-cbc"; 
	return 1;
}

/*ARGSUSED*/
static int opt_act_33_2(menudesc *m, void *arg)
{
	 *(const char**)arg = "3des-cbc"; 
	return 1;
}

/*ARGSUSED*/
static int opt_act_33_3(menudesc *m, void *arg)
{
	 *(const char**)arg = "blowfish-cbc"; 
	return 1;
}

/*ARGSUSED*/
static int opt_act_34_0(menudesc *m, void *arg)
{
	 *(const char**)arg = "encblkno1"; 
	return 1;
}

/*ARGSUSED*/
static int opt_act_34_1(menudesc *m, void *arg)
{
	 *(const char**)arg = "encblkno8"; 
	return 1;
}

/*ARGSUSED*/
static int opt_act_35_0(menudesc *m, void *arg)
{
	 *(const char**)arg = "pkcs5_pbkdf2/sha1"; 
	return 1;
}

/*ARGSUSED*/
static int opt_act_35_1(menudesc *m, void *arg)
{
	 *(const char**)arg = "pkcs5_pbkdf2"; 
	return 1;
}

/*ARGSUSED*/
static int opt_act_35_2(menudesc *m, void *arg)
{
	 *(const char**)arg = "storedkey"; 
	return 1;
}

/*ARGSUSED*/
static int opt_act_35_3(menudesc *m, void *arg)
{
	 *(const char**)arg = "randomkey"; 
	return 1;
}

/*ARGSUSED*/
static int opt_act_35_4(menudesc *m, void *arg)
{
	 *(const char**)arg = "urandomkey"; 
	return 1;
}

/*ARGSUSED*/
static int opt_act_35_5(menudesc *m, void *arg)
{
	 *(const char**)arg = "shell_cmd"; 
	return 1;
}

/*ARGSUSED*/
static int opt_act_36_0(menudesc *m, void *arg)
{
	 *(const char**)arg = "none"; 
	return 1;
}

/*ARGSUSED*/
static int opt_act_36_1(menudesc *m, void *arg)
{
	 *(const char**)arg = "disklabel"; 
	return 1;
}

/*ARGSUSED*/
static int opt_act_36_2(menudesc *m, void *arg)
{
	 *(const char**)arg = "mbr"; 
	return 1;
}

/*ARGSUSED*/
static int opt_act_36_3(menudesc *m, void *arg)
{
	 *(const char**)arg = "gpt"; 
	return 1;
}

/*ARGSUSED*/
static int opt_act_36_4(menudesc *m, void *arg)
{
	 *(const char**)arg = "ffs"; 
	return 1;
}

/*ARGSUSED*/
static int opt_act_36_5(menudesc *m, void *arg)
{
	 *(const char**)arg = "re-enter"; 
	return 1;
}

/*ARGSUSED*/
static int opt_act_37_0(menudesc *m, void *arg)
{
	 *((int*)arg) = 1; 
	return 1;
}

/*ARGSUSED*/
static int opt_act_37_1(menudesc *m, void *arg)
{
	 *((int*)arg) = 2; 
	return 1;
}

/*ARGSUSED*/
static int opt_act_37_2(menudesc *m, void *arg)
{
	 *((int*)arg) = 3; 
	return 1;
}

/*ARGSUSED*/
static int opt_act_37_3(menudesc *m, void *arg)
{
	 *((int*)arg) = 4; 
	return 1;
}

/*ARGSUSED*/
static int opt_act_38_0(menudesc *m, void *arg)
{
	 *((int*)arg) = 1; 
	return 1;
}

/*ARGSUSED*/
static int opt_act_38_1(menudesc *m, void *arg)
{
	 *((int*)arg) = 2; 
	return 1;
}

/*ARGSUSED*/
static int opt_act_38_2(menudesc *m, void *arg)
{
	 *((int*)arg) = 3; 
	return 1;
}

/*ARGSUSED*/
static int opt_act_38_3(menudesc *m, void *arg)
{
	 *((int*)arg) = 4; 
	return 1;
}

/*ARGSUSED*/
static int opt_act_39_0(menudesc *m, void *arg)
{
	 src_prompt(MSG_Host, nfs_host, sizeof nfs_host); 
	return 0;
}

/*ARGSUSED*/
static int opt_act_39_1(menudesc *m, void *arg)
{
	 src_prompt(MSG_Base_dir, nfs_dir, sizeof nfs_dir); 
	return 0;
}

/*ARGSUSED*/
static int opt_act_39_2(menudesc *m, void *arg)
{
	 src_prompt(MSG_set_entropy_file, entropy_file, sizeof entropy_file); 
	return 0;
}

/*ARGSUSED*/
static int opt_act_39_3(menudesc *m, void *arg)
{
	 *((int*)arg) = SET_RETRY; 
	return 1;
}

/*ARGSUSED*/
static int opt_act_40_0(menudesc *m, void *arg)
{
	 struct ftpinfo *fpi = (struct ftpinfo*)((arg_rv*)arg)->arg;
			src_prompt(MSG_Host,
			fpi->xfer_host[XFER_HOST(fpi->xfer)],
			sizeof fpi->xfer_host[XFER_HOST(fpi->xfer)]); 
	return 0;
}

/*ARGSUSED*/
static int opt_act_40_1(menudesc *m, void *arg)
{
	 src_prompt(MSG_entropy_path_and_file,
			entropy_file, sizeof entropy_file); 
	return 0;
}

/*ARGSUSED*/
static int opt_act_40_2(menudesc *m, void *arg)
{
	 struct ftpinfo *fpi = (struct ftpinfo*)((arg_rv*)arg)->arg;
			src_prompt(MSG_User, fpi->user, sizeof fpi->user);
			fpi->pass[0] = 0;
		
	return 0;
}

/*ARGSUSED*/
static int opt_act_40_3(menudesc *m, void *arg)
{
	 struct ftpinfo *fpi = (struct ftpinfo*)((arg_rv*)arg)->arg;
			if (strcmp(fpi->user, "ftp") == 0)
			src_prompt(MSG_email, fpi->pass, sizeof fpi->pass);
		  else {
			msg_prompt_noecho(MSG_Password, "",
					fpi->pass, sizeof fpi->pass);
		  }
		
	return 0;
}

/*ARGSUSED*/
static int opt_act_40_4(menudesc *m, void *arg)
{
	 struct ftpinfo *fpi = (struct ftpinfo*)((arg_rv*)arg)->arg;
			src_prompt(MSG_Proxy, fpi->proxy, sizeof fpi->proxy);
			if (strcmp(fpi->proxy, "") == 0) {
				unsetenv("ftp_proxy");
				unsetenv("http_proxy");
			} else {
				setenv("ftp_proxy", fpi->proxy, 1);
				setenv("http_proxy", fpi->proxy, 1);
			}
		
	return 0;
}

/*ARGSUSED*/
static int opt_act_40_5(menudesc *m, void *arg)
{
	 ((arg_rv*)arg)->rv = SET_RETRY; 
	return 1;
}

/*ARGSUSED*/
static void menu_41_postact(menudesc *menu, void *arg)
{
	 msg_display(MSG_entropy_localfs); 
}

/*ARGSUSED*/
static int opt_act_41_0(menudesc *m, void *arg)
{
	 src_prompt(MSG_dev, localfs_dev, sizeof localfs_dev);
	return 0;
}

/*ARGSUSED*/
static int opt_act_41_1(menudesc *m, void *arg)
{
	 src_prompt(MSG_filesys, localfs_fs, sizeof localfs_fs); 
	return 0;
}

/*ARGSUSED*/
static int opt_act_41_2(menudesc *m, void *arg)
{
	 src_prompt(MSG_entropy_path_and_file, entropy_file, sizeof entropy_file);
	return 0;
}

/*ARGSUSED*/
static int opt_act_41_3(menudesc *m, void *arg)
{
	 *((int*)arg) = SET_RETRY; 
	return 1;
}

/*ARGSUSED*/
static void menu_42_postact(menudesc *menu, void *arg)
{
	 msg_display(MSG_getboottype);
		switch (((struct x86_boot_params *)arg)->bp_consdev) {
		default:
		case 0:
			msg_display_add(MSG_console_PC);
			break;
		case 1: case 2: case 3: case 4:
			if (menu->cursel == 0)
			    menu->cursel = ((struct x86_boot_params *)arg)->bp_consdev;
			msg_fmt_display_add(MSG_console_com, "%u%u",
			    ((struct x86_boot_params *)arg)->bp_consdev - 1,
			    ((struct x86_boot_params *)arg)->bp_conspeed);
			break;
		case ~0:
			msg_display_add(MSG_console_unchanged);
			break;
		}
}

/*ARGSUSED*/
static int opt_act_42_0(menudesc *m, void *arg)
{
	((struct x86_boot_params *)arg)->bp_consdev = 0; m->cursel = 7;
	return 1;
}

/*ARGSUSED*/
static int opt_act_42_1(menudesc *m, void *arg)
{
	((struct x86_boot_params *)arg)->bp_consdev = 1; m->cursel = 5;
	return 0;
}

/*ARGSUSED*/
static int opt_act_42_2(menudesc *m, void *arg)
{
	((struct x86_boot_params *)arg)->bp_consdev = 2; m->cursel = 5;
	return 0;
}

/*ARGSUSED*/
static int opt_act_42_3(menudesc *m, void *arg)
{
	((struct x86_boot_params *)arg)->bp_consdev = 3; m->cursel = 5;
	return 0;
}

/*ARGSUSED*/
static int opt_act_42_4(menudesc *m, void *arg)
{
	((struct x86_boot_params *)arg)->bp_consdev = 4; m->cursel = 5;
	return 0;
}

/*ARGSUSED*/
static int opt_act_42_6(menudesc *m, void *arg)
{
	((struct x86_boot_params *)arg)->bp_consdev = ~0; m->cursel = 7;
	return 1;
}

/*ARGSUSED*/
static void menu_43_postact(menudesc *menu, void *arg)
{
	
		switch (((struct x86_boot_params *)arg)->bp_conspeed) {
		default:
		case   9600: menu->cursel = 0; break;
		case  19200: menu->cursel = 1; break;
		case  38400: menu->cursel = 2; break;
		case  57600: menu->cursel = 3; break;
		case 115200: menu->cursel = 4; break;
		case      0: menu->cursel = 5; break;
		}
}

/*ARGSUSED*/
static int opt_act_43_0(menudesc *m, void *arg)
{
	((struct x86_boot_params *)arg)->bp_conspeed = 9600;
	return 1;
}

/*ARGSUSED*/
static int opt_act_43_1(menudesc *m, void *arg)
{
	((struct x86_boot_params *)arg)->bp_conspeed = 19200;
	return 1;
}

/*ARGSUSED*/
static int opt_act_43_2(menudesc *m, void *arg)
{
	((struct x86_boot_params *)arg)->bp_conspeed = 38400;
	return 1;
}

/*ARGSUSED*/
static int opt_act_43_3(menudesc *m, void *arg)
{
	((struct x86_boot_params *)arg)->bp_conspeed = 57600;
	return 1;
}

/*ARGSUSED*/
static int opt_act_43_4(menudesc *m, void *arg)
{
	((struct x86_boot_params *)arg)->bp_conspeed = 115200;
	return 1;
}

/*ARGSUSED*/
static int opt_act_43_5(menudesc *m, void *arg)
{
	((struct x86_boot_params *)arg)->bp_conspeed = 0;
	return 1;
}

/*ARGSUSED*/
static int opt_act_44_0(menudesc *m, void *arg)
{
	 
	return 1;
}

/*ARGSUSED*/
static int opt_act_44_1(menudesc *m, void *arg)
{
	*(void **)arg = NULL;
	return 1;
}

/*ARGSUSED*/
static int opt_act_45_0(menudesc *m, void *arg)
{
	
		int sel;
		char res[4];

		do {
			strcpy(res, "0");
			msg_prompt_win(MSG_pickdisk, -1, -1, 0, 0,
					res, res, sizeof res);
			sel = atoi(res);
		} while (sel < 0 || sel >= *(int *)arg);
		*(int *)arg = sel;
	
	return 1;
}

/*ARGSUSED*/
static int opt_act_45_1(menudesc *m, void *arg)
{
	
		*(int *)arg = -1;
	
	return 1;
}

static menu_ent optent1[] = {
	{ .opt_name = "log", .opt_menu=0, .opt_flags=4, .opt_action=opt_act_1_0},
	{ .opt_name = "async", .opt_menu=0, .opt_flags=4, .opt_action=opt_act_1_1},
	{ .opt_name = "noatime", .opt_menu=0, .opt_flags=4, .opt_action=opt_act_1_2},
	{ .opt_name = "nodev", .opt_menu=0, .opt_flags=4, .opt_action=opt_act_1_3},
	{ .opt_name = "nodevmtime", .opt_menu=0, .opt_flags=4, .opt_action=opt_act_1_4},
	{ .opt_name = "noexec", .opt_menu=0, .opt_flags=4, .opt_action=opt_act_1_5},
	{ .opt_name = "nosuid", .opt_menu=0, .opt_flags=4, .opt_action=opt_act_1_6},
	{ .opt_name = "noauto", .opt_menu=0, .opt_flags=4, .opt_action=opt_act_1_7}
	};

static menu_ent optent2[] = {
	{ .opt_name = MSG_Install_NetBSD_to_hard_disk, .opt_menu=0, .opt_flags=0, .opt_action=opt_act_2_0},
	{ .opt_name = MSG_Upgrade_NetBSD_on_a_hard_disk, .opt_menu=0, .opt_flags=0, .opt_action=opt_act_2_1},
	{ .opt_name = MSG_Re_install_sets_or_install_additional_sets, .opt_menu=0, .opt_flags=0, .opt_action=opt_act_2_2},
	{ .opt_name = MSG_Reboot_the_computer, .opt_menu=0, .opt_flags=6, .opt_action=opt_act_2_3},
	{ .opt_name = MSG_Utility_menu, .opt_menu=3, .opt_flags=1, .opt_action=NULL},
	{ .opt_name = MSG_Config_menu, .opt_menu=0, .opt_flags=0, .opt_action=opt_act_2_5}
	};

static menu_ent optent3[] = {
	{ .opt_name = MSG_Run_bin_sh, .opt_menu=0, .opt_flags=2, .opt_action=opt_act_3_0},
	{ .opt_name = MSG_Set_timezone, .opt_menu=0, .opt_flags=0, .opt_action=opt_act_3_1},
	{ .opt_name = MSG_Configure_network, .opt_menu=0, .opt_flags=0, .opt_action=opt_act_3_2},
	{ .opt_name = MSG_Partition_a_disk, .opt_menu=0, .opt_flags=0, .opt_action=opt_act_3_3},
	{ .opt_name = MSG_Logging_functions, .opt_menu=0, .opt_flags=0, .opt_action=opt_act_3_4},
	{ .opt_name = MSG_Color_scheme, .opt_menu=4, .opt_flags=1, .opt_action=NULL},
	{ .opt_name = MSG_Halt_the_system, .opt_menu=0, .opt_flags=6, .opt_action=opt_act_3_6}
	};

static menu_ent optent4[] = {
	{ .opt_name = MSG_White_on_black, .opt_menu=0, .opt_flags=0, .opt_action=opt_act_4_0},
	{ .opt_name = MSG_Black_on_white, .opt_menu=0, .opt_flags=0, .opt_action=opt_act_4_1},
	{ .opt_name = MSG_White_on_blue, .opt_menu=0, .opt_flags=0, .opt_action=opt_act_4_2},
	{ .opt_name = MSG_Green_on_black, .opt_menu=0, .opt_flags=0, .opt_action=opt_act_4_3}
	};

static menu_ent optent5[] = {
	{ .opt_name = MSG_Yes, .opt_menu=0, .opt_flags=4, .opt_action=opt_act_5_0},
	{ .opt_name = MSG_No, .opt_menu=0, .opt_flags=4, .opt_action=opt_act_5_1}
	};

static menu_ent optent6[] = {
	{ .opt_name = MSG_No, .opt_menu=0, .opt_flags=4, .opt_action=opt_act_6_0},
	{ .opt_name = MSG_Yes, .opt_menu=0, .opt_flags=4, .opt_action=opt_act_6_1}
	};

static menu_ent optent7[] = {
	{ .opt_name = MSG_Hit_enter_to_continue, .opt_menu=0, .opt_flags=4, .opt_action=NULL}
	};

static menu_ent optent8[] = {
	{ .opt_name = MSG_Gigabytes, .opt_menu=0, .opt_flags=4, .opt_action=opt_act_8_0},
	{ .opt_name = MSG_Megabytes, .opt_menu=0, .opt_flags=4, .opt_action=opt_act_8_1},
	{ .opt_name = MSG_Cylinders, .opt_menu=0, .opt_flags=4, .opt_action=opt_act_8_2},
	{ .opt_name = MSG_Sectors, .opt_menu=0, .opt_flags=4, .opt_action=opt_act_8_3}
	};

static menu_ent optent9[] = {
	{ .opt_name = MSG_Yes, .opt_menu=0, .opt_flags=4, .opt_action=opt_act_9_0},
	{ .opt_name = MSG_cancel, .opt_menu=0, .opt_flags=4, .opt_action=opt_act_9_1}
	};

static menu_ent optent10[] = {
	{ .opt_name = MSG_cdrom, .opt_menu=0, .opt_flags=4, .opt_action=opt_act_10_0},
	{ .opt_name = MSG_http, .opt_menu=0, .opt_flags=4, .opt_action=opt_act_10_1},
	{ .opt_name = MSG_ftp, .opt_menu=0, .opt_flags=4, .opt_action=opt_act_10_2},
	{ .opt_name = MSG_nfs, .opt_menu=0, .opt_flags=4, .opt_action=opt_act_10_3},
	{ .opt_name = MSG_floppy, .opt_menu=0, .opt_flags=4, .opt_action=opt_act_10_4},
	{ .opt_name = MSG_local_fs, .opt_menu=0, .opt_flags=4, .opt_action=opt_act_10_5},
	{ .opt_name = MSG_local_dir, .opt_menu=0, .opt_flags=4, .opt_action=opt_act_10_6},
	{ .opt_name = MSG_Skip_set, .opt_menu=0, .opt_flags=4, .opt_action=opt_act_10_7},
	{ .opt_name = MSG_Skip_group, .opt_menu=0, .opt_flags=4, .opt_action=opt_act_10_8},
	{ .opt_name = MSG_Abandon, .opt_menu=0, .opt_flags=4, .opt_action=opt_act_10_9}
	};

static menu_ent optent11[] = {
	{ .opt_name = MSG_Full_installation, .opt_menu=0, .opt_flags=4, .opt_action=opt_act_11_0},
	{ .opt_name = MSG_Full_installation_nox, .opt_menu=0, .opt_flags=4, .opt_action=opt_act_11_1},
	{ .opt_name = MSG_Minimal_installation, .opt_menu=0, .opt_flags=4, .opt_action=opt_act_11_2},
	{ .opt_name = MSG_Custom_installation, .opt_menu=0, .opt_flags=4, .opt_action=opt_act_11_3}
	};

static menu_ent optent12[] = {
	{ .opt_name = 0, .opt_menu=0, .opt_flags=0, .opt_action=opt_act_12_0},
	{ .opt_name = 0, .opt_menu=0, .opt_flags=0, .opt_action=opt_act_12_1},
	{ .opt_name = 0, .opt_menu=0, .opt_flags=0, .opt_action=opt_act_12_2},
	{ .opt_name = 0, .opt_menu=0, .opt_flags=0, .opt_action=opt_act_12_3},
	{ .opt_name = 0, .opt_menu=0, .opt_flags=0, .opt_action=opt_act_12_4},
	{ .opt_name = 0, .opt_menu=0, .opt_flags=0, .opt_action=opt_act_12_5},
	{ .opt_name = 0, .opt_menu=0, .opt_flags=0, .opt_action=opt_act_12_6},
	{ .opt_name = 0, .opt_menu=0, .opt_flags=0, .opt_action=opt_act_12_7},
	{ .opt_name = 0, .opt_menu=0, .opt_flags=0, .opt_action=opt_act_12_8},
	{ .opt_name = 0, .opt_menu=0, .opt_flags=0, .opt_action=opt_act_12_9},
	{ .opt_name = MSG_Configure_network, .opt_menu=0, .opt_flags=0, .opt_action=opt_act_12_10},
	{ .opt_name = MSG_exit_menu_generic, .opt_menu=0, .opt_flags=4, .opt_action=opt_act_12_11}
	};

static void menu_12_legend(menudesc *menu, int opt, void *arg)
{
	switch (opt) {
	case 0:
		{src_legend(menu, MSG_Host, ftp.xfer_host[
		XFER_HOST((uintptr_t)((arg_rv*)arg)->arg)]);};
		break;
	case 1:
		{src_legend(menu, MSG_Base_dir, ftp.dir);};
		break;
	case 2:
		{src_legend(menu, MSG_Set_dir_bin, set_dir_bin);};
		break;
	case 3:
		{src_legend(menu, MSG_Set_dir_src, set_dir_src);};
		break;
	case 4:
		{src_legend(menu, MSG_Dist_postfix, dist_postfix);};
		break;
	case 5:
		{src_legend(menu, MSG_User, ftp.user);};
		break;
	case 6:
		{src_legend(menu, MSG_Password,
		    strcmp(ftp.user, "ftp") == 0 || ftp.pass[0] == 0
			? ftp.pass : msg_string(MSG_hidden));};
		break;
	case 7:
		{src_legend(menu, MSG_Proxy, ftp.proxy);};
		break;
	case 8:
		{src_legend(menu, MSG_Xfer_dir, xfer_dir);};
		break;
	case 9:
		{src_legend(menu, MSG_delete_xfer_file,
			clean_xfer_dir ? MSG_Yes : MSG_No);};
		break;
	}
}

static menu_ent optent13[] = {
	{ .opt_name = 0, .opt_menu=0, .opt_flags=0, .opt_action=opt_act_13_0},
	{ .opt_name = 0, .opt_menu=0, .opt_flags=0, .opt_action=opt_act_13_1},
	{ .opt_name = 0, .opt_menu=0, .opt_flags=0, .opt_action=opt_act_13_2},
	{ .opt_name = 0, .opt_menu=0, .opt_flags=0, .opt_action=opt_act_13_3},
	{ .opt_name = 0, .opt_menu=0, .opt_flags=0, .opt_action=opt_act_13_4},
	{ .opt_name = MSG_Configure_network, .opt_menu=0, .opt_flags=0, .opt_action=opt_act_13_5},
	{ .opt_name = MSG_exit_menu_generic, .opt_menu=0, .opt_flags=4, .opt_action=opt_act_13_6}
	};

static void menu_13_legend(menudesc *menu, int opt, void *arg)
{
	switch (opt) {
	case 0:
		{src_legend(menu, MSG_Host, nfs_host);};
		break;
	case 1:
		{src_legend(menu, MSG_Base_dir, nfs_dir);};
		break;
	case 2:
		{src_legend(menu, MSG_Set_dir_bin, set_dir_bin);};
		break;
	case 3:
		{src_legend(menu, MSG_Set_dir_src, set_dir_src);};
		break;
	case 4:
		{src_legend(menu, MSG_Dist_postfix, dist_postfix);};
		break;
	}
}

static menu_ent optent14[] = {
	{ .opt_name = MSG_Try_again, .opt_menu=0, .opt_flags=4, .opt_action=opt_act_14_0},
	{ .opt_name = MSG_Set_finished, .opt_menu=0, .opt_flags=4, .opt_action=opt_act_14_1},
	{ .opt_name = MSG_Abort_fetch, .opt_menu=0, .opt_flags=4, .opt_action=opt_act_14_2}
	};

static menu_ent optent15[] = {
	{ .opt_name = MSG_OK, .opt_menu=0, .opt_flags=4, .opt_action=opt_act_15_0},
	{ .opt_name = MSG_Set_finished, .opt_menu=0, .opt_flags=4, .opt_action=opt_act_15_1},
	{ .opt_name = MSG_Abort_fetch, .opt_menu=0, .opt_flags=4, .opt_action=opt_act_15_2}
	};

static menu_ent optent16[] = {
	{ .opt_name = "msdos", .opt_menu=0, .opt_flags=4, .opt_action=opt_act_16_0},
	{ .opt_name = "ffs", .opt_menu=0, .opt_flags=4, .opt_action=opt_act_16_1}
	};

static menu_ent optent17[] = {
	{ .opt_name = 0, .opt_menu=0, .opt_flags=0, .opt_action=opt_act_17_0},
	{ .opt_name = 0, .opt_menu=16, .opt_flags=1, .opt_action=NULL},
	{ .opt_name = 0, .opt_menu=0, .opt_flags=0, .opt_action=opt_act_17_2},
	{ .opt_name = 0, .opt_menu=0, .opt_flags=0, .opt_action=opt_act_17_3},
	{ .opt_name = MSG_exit_menu_generic, .opt_menu=0, .opt_flags=4, .opt_action=opt_act_17_4}
	};

static void menu_17_legend(menudesc *menu, int opt, void *arg)
{
	switch (opt) {
	case 0:
		{src_legend(menu, MSG_Device, fd_dev);};
		break;
	case 1:
		{src_legend(menu, MSG_fd_type, fd_type);};
		break;
	case 2:
		{src_legend(menu, MSG_Xfer_dir, xfer_dir);};
		break;
	case 3:
		{src_legend(menu, MSG_delete_xfer_file,
			clean_xfer_dir ? MSG_Yes : MSG_No);};
		break;
	}
}

static menu_ent optent18[] = {
	{ .opt_name = 0, .opt_menu=0, .opt_flags=0, .opt_action=opt_act_18_0},
	{ .opt_name = 0, .opt_menu=0, .opt_flags=0, .opt_action=opt_act_18_1},
	{ .opt_name = 0, .opt_menu=0, .opt_flags=0, .opt_action=opt_act_18_2},
	{ .opt_name = 0, .opt_menu=0, .opt_flags=0, .opt_action=opt_act_18_3},
	{ .opt_name = MSG_abort_install, .opt_menu=0, .opt_flags=4, .opt_action=opt_act_18_4},
	{ .opt_name = MSG_source_sel_retry, .opt_menu=0, .opt_flags=4, .opt_action=opt_act_18_5}
	};

static void menu_18_legend(menudesc *menu, int opt, void *arg)
{
	switch (opt) {
	case 0:
		{src_legend(menu, MSG_Device, cdrom_dev);};
		break;
	case 1:
		{src_legend(menu, MSG_Set_dir_bin, set_dir_bin);};
		break;
	case 2:
		{src_legend(menu, MSG_Set_dir_src, set_dir_src);};
		break;
	case 3:
		{src_legend(menu, MSG_Dist_postfix, dist_postfix);};
		break;
	}
}

static menu_ent optent19[] = {
	{ .opt_name = 0, .opt_menu=0, .opt_flags=0, .opt_action=opt_act_19_0},
	{ .opt_name = 0, .opt_menu=0, .opt_flags=0, .opt_action=opt_act_19_1},
	{ .opt_name = 0, .opt_menu=0, .opt_flags=0, .opt_action=opt_act_19_2},
	{ .opt_name = 0, .opt_menu=0, .opt_flags=0, .opt_action=opt_act_19_3},
	{ .opt_name = 0, .opt_menu=0, .opt_flags=0, .opt_action=opt_act_19_4},
	{ .opt_name = 0, .opt_menu=0, .opt_flags=0, .opt_action=opt_act_19_5},
	{ .opt_name = MSG_exit_menu_generic, .opt_menu=0, .opt_flags=4, .opt_action=opt_act_19_6}
	};

static void menu_19_legend(menudesc *menu, int opt, void *arg)
{
	switch (opt) {
	case 0:
		{src_legend(menu, MSG_Device, localfs_dev);};
		break;
	case 1:
		{src_legend(menu, MSG_File_system, localfs_fs);};
		break;
	case 2:
		{src_legend(menu, MSG_Base_dir, localfs_dir);};
		break;
	case 3:
		{src_legend(menu, MSG_Set_dir_bin, set_dir_bin);};
		break;
	case 4:
		{src_legend(menu, MSG_Set_dir_src, set_dir_src);};
		break;
	case 5:
		{src_legend(menu, MSG_Dist_postfix, dist_postfix);};
		break;
	}
}

static menu_ent optent20[] = {
	{ .opt_name = 0, .opt_menu=0, .opt_flags=0, .opt_action=opt_act_20_0},
	{ .opt_name = 0, .opt_menu=0, .opt_flags=0, .opt_action=opt_act_20_1},
	{ .opt_name = 0, .opt_menu=0, .opt_flags=0, .opt_action=opt_act_20_2},
	{ .opt_name = 0, .opt_menu=0, .opt_flags=0, .opt_action=opt_act_20_3},
	{ .opt_name = MSG_exit_menu_generic, .opt_menu=0, .opt_flags=4, .opt_action=opt_act_20_4}
	};

static void menu_20_legend(menudesc *menu, int opt, void *arg)
{
	switch (opt) {
	case 0:
		{src_legend(menu, MSG_Base_dir, localfs_dir);};
		break;
	case 1:
		{src_legend(menu, MSG_Set_dir_bin, set_dir_bin);};
		break;
	case 2:
		{src_legend(menu, MSG_Set_dir_src, set_dir_src);};
		break;
	case 3:
		{src_legend(menu, MSG_Dist_postfix, dist_postfix);};
		break;
	}
}

static menu_ent optent21[] = {
	{ .opt_name = "google-public-dns-a.google.com (IPv4)", .opt_menu=0, .opt_flags=4, .opt_action=opt_act_21_0},
	{ .opt_name = "google-public-dns-b.google.com (IPv4)", .opt_menu=0, .opt_flags=4, .opt_action=opt_act_21_1},
	{ .opt_name = "google-public-dns-a.google.com (IPv6)", .opt_menu=0, .opt_flags=4, .opt_action=opt_act_21_2},
	{ .opt_name = "google-public-dns-b.google.com (IPv6)", .opt_menu=0, .opt_flags=4, .opt_action=opt_act_21_3},
	{ .opt_name = MSG_other, .opt_menu=0, .opt_flags=4, .opt_action=opt_act_21_4}
	};

static menu_ent optent22[] = {
	{ .opt_name = "/bin/sh", .opt_menu=0, .opt_flags=4, .opt_action=opt_act_22_0},
	{ .opt_name = "/bin/ksh", .opt_menu=0, .opt_flags=4, .opt_action=opt_act_22_1},
	{ .opt_name = "/bin/csh", .opt_menu=0, .opt_flags=4, .opt_action=opt_act_22_2}
	};

static menu_ent optent23[] = {
	{ .opt_name = "run mdnsd only", .opt_menu=0, .opt_flags=4, .opt_action=opt_act_23_0},
	{ .opt_name = "run mdnsd and resolve local names", .opt_menu=0, .opt_flags=4, .opt_action=opt_act_23_1},
	{ .opt_name = "do not run mdnsd", .opt_menu=0, .opt_flags=4, .opt_action=opt_act_23_2}
	};

static menu_ent optent24[] = {
	{ .opt_name = 0, .opt_menu=0, .opt_flags=0, .opt_action=opt_act_24_0},
	{ .opt_name = 0, .opt_menu=0, .opt_flags=0, .opt_action=opt_act_24_1},
	{ .opt_name = 0, .opt_menu=0, .opt_flags=0, .opt_action=opt_act_24_2},
	{ .opt_name = 0, .opt_menu=0, .opt_flags=0, .opt_action=opt_act_24_3},
	{ .opt_name = 0, .opt_menu=0, .opt_flags=0, .opt_action=opt_act_24_4},
	{ .opt_name = 0, .opt_menu=0, .opt_flags=0, .opt_action=opt_act_24_5},
	{ .opt_name = 0, .opt_menu=0, .opt_flags=0, .opt_action=opt_act_24_6},
	{ .opt_name = MSG_Configure_network, .opt_menu=0, .opt_flags=0, .opt_action=opt_act_24_7},
	{ .opt_name = 0, .opt_menu=0, .opt_flags=0, .opt_action=opt_act_24_8},
	{ .opt_name = MSG_quit_pkgs_install, .opt_menu=0, .opt_flags=4, .opt_action=opt_act_24_9}
	};

static void menu_24_legend(menudesc *menu, int opt, void *arg)
{
	switch (opt) {
	case 0:
		{src_legend(menu, MSG_Host,
		pkg.xfer_host[XFER_HOST(pkg.xfer)]);};
		break;
	case 1:
		{src_legend(menu, MSG_Base_dir, pkg.dir);};
		break;
	case 2:
		{src_legend(menu, MSG_Pkg_dir, pkg_dir);};
		break;
	case 3:
		{src_legend(menu, MSG_User, pkg.user);};
		break;
	case 4:
		{src_legend(menu, MSG_Password,
		    strcmp(pkg.user, "ftp") == 0 || pkg.pass[0] == 0
			? pkg.pass : msg_string(MSG_hidden));};
		break;
	case 5:
		{src_legend(menu, MSG_Proxy, pkg.proxy);};
		break;
	case 6:
		{src_legend(menu, "Additional packages", (char*)(((arg_rv*)arg)->arg)); };
		break;
	case 8:
		{src_legend(menu, MSG_transfer_method, url_proto(pkg.xfer));};
		break;
	}
}

static menu_ent optent25[] = {
	{ .opt_name = 0, .opt_menu=0, .opt_flags=0, .opt_action=opt_act_25_0},
	{ .opt_name = 0, .opt_menu=0, .opt_flags=0, .opt_action=opt_act_25_1},
	{ .opt_name = 0, .opt_menu=0, .opt_flags=0, .opt_action=opt_act_25_2},
	{ .opt_name = 0, .opt_menu=0, .opt_flags=0, .opt_action=opt_act_25_3},
	{ .opt_name = 0, .opt_menu=0, .opt_flags=0, .opt_action=opt_act_25_4},
	{ .opt_name = 0, .opt_menu=0, .opt_flags=0, .opt_action=opt_act_25_5},
	{ .opt_name = 0, .opt_menu=0, .opt_flags=0, .opt_action=opt_act_25_6},
	{ .opt_name = 0, .opt_menu=0, .opt_flags=0, .opt_action=opt_act_25_7},
	{ .opt_name = MSG_quit_pkgsrc, .opt_menu=0, .opt_flags=4, .opt_action=opt_act_25_8}
	};

static void menu_25_legend(menudesc *menu, int opt, void *arg)
{
	switch (opt) {
	case 0:
		{src_legend(menu, MSG_Host, pkgsrc.xfer_host[
		XFER_HOST(pkgsrc.xfer)]);};
		break;
	case 1:
		{src_legend(menu, MSG_Pkgsrc_dir, pkgsrc_dir);};
		break;
	case 2:
		{src_legend(menu, MSG_User, pkgsrc.user);};
		break;
	case 3:
		{src_legend(menu, MSG_Password,
		    strcmp(pkgsrc.user, "ftp") == 0 || pkgsrc.pass[0] == 0
			? pkgsrc.pass : msg_string(MSG_hidden));};
		break;
	case 4:
		{src_legend(menu, MSG_Proxy, pkgsrc.proxy);};
		break;
	case 5:
		{src_legend(menu, MSG_Xfer_dir, xfer_dir);};
		break;
	case 6:
		{src_legend(menu, MSG_delete_xfer_file,
			clean_xfer_dir ? MSG_Yes : MSG_No);};
		break;
	case 7:
		{src_legend(menu, MSG_transfer_method, url_proto(pkgsrc.xfer));};
		break;
	}
}

static menu_ent optent26[] = {
	{ .opt_name = "/bin/sh", .opt_menu=0, .opt_flags=4, .opt_action=opt_act_26_0},
	{ .opt_name = "/bin/ksh", .opt_menu=0, .opt_flags=4, .opt_action=opt_act_26_1},
	{ .opt_name = "/bin/csh", .opt_menu=0, .opt_flags=4, .opt_action=opt_act_26_2}
	};

static menu_ent optent27[] = {
	{ .opt_name = MSG_cvtscheme_keep, .opt_menu=0, .opt_flags=4, .opt_action=opt_act_27_0},
	{ .opt_name = MSG_cvtscheme_delete, .opt_menu=0, .opt_flags=4, .opt_action=opt_act_27_1},
	{ .opt_name = MSG_cvtscheme_convert, .opt_menu=0, .opt_flags=4, .opt_action=opt_act_27_2},
	{ .opt_name = MSG_cvtscheme_abort, .opt_menu=0, .opt_flags=4, .opt_action=opt_act_27_3}
	};

static menu_ent optent28[] = {
	{ .opt_name = MSG_reedit_partitions, .opt_menu=0, .opt_flags=4, .opt_action=opt_act_28_0},
	{ .opt_name = MSG_use_partitions_anyway, .opt_menu=0, .opt_flags=4, .opt_action=opt_act_28_1},
	{ .opt_name = MSG_abort_installation, .opt_menu=0, .opt_flags=4, .opt_action=opt_act_28_2}
	};

static menu_ent optent29[] = {
	{ .opt_name = MSG_edit_parts, .opt_menu=0, .opt_flags=4, .opt_action=opt_act_29_0},
	{ .opt_name = MSG_switch_parts, .opt_menu=0, .opt_flags=4, .opt_action=opt_act_29_1},
	{ .opt_name = MSG_fmtasraid, .opt_menu=0, .opt_flags=4, .opt_action=opt_act_29_2},
	{ .opt_name = MSG_fmtaslvm, .opt_menu=0, .opt_flags=4, .opt_action=opt_act_29_3},
	{ .opt_name = MSG_encrypt, .opt_menu=0, .opt_flags=4, .opt_action=opt_act_29_4},
	{ .opt_name = MSG_erase, .opt_menu=30, .opt_flags=0, .opt_action=NULL},
	{ .opt_name = MSG_undo, .opt_menu=0, .opt_flags=4, .opt_action=opt_act_29_6},
	{ .opt_name = MSG_unconfig, .opt_menu=0, .opt_flags=4, .opt_action=opt_act_29_7}
	};

static menu_ent optent30[] = {
	{ .opt_name = MSG_fillzeros, .opt_menu=0, .opt_flags=4, .opt_action=opt_act_30_0},
	{ .opt_name = MSG_fillrandom, .opt_menu=0, .opt_flags=4, .opt_action=opt_act_30_1}
	};

static menu_ent optent31[] = {
	{ .opt_name = MSG_edit, .opt_menu=0, .opt_flags=4, .opt_action=opt_act_31_0},
	{ .opt_name = MSG_fmtasraid, .opt_menu=0, .opt_flags=4, .opt_action=opt_act_31_1},
	{ .opt_name = MSG_fmtaslvm, .opt_menu=0, .opt_flags=4, .opt_action=opt_act_31_2},
	{ .opt_name = MSG_encrypt, .opt_menu=0, .opt_flags=4, .opt_action=opt_act_31_3},
	{ .opt_name = MSG_erase, .opt_menu=30, .opt_flags=0, .opt_action=NULL},
	{ .opt_name = MSG_doumount, .opt_menu=0, .opt_flags=4, .opt_action=opt_act_31_5},
	{ .opt_name = MSG_Delete_partition, .opt_menu=0, .opt_flags=4, .opt_action=opt_act_31_6}
	};

static menu_ent optent32[] = {
	{ .opt_name = MSG_raid0, .opt_menu=0, .opt_flags=4, .opt_action=opt_act_32_0},
	{ .opt_name = MSG_raid1, .opt_menu=0, .opt_flags=4, .opt_action=opt_act_32_1},
	{ .opt_name = MSG_raid4, .opt_menu=0, .opt_flags=4, .opt_action=opt_act_32_2},
	{ .opt_name = MSG_raid5, .opt_menu=0, .opt_flags=4, .opt_action=opt_act_32_3}
	};

static menu_ent optent33[] = {
	{ .opt_name = "aes-xts", .opt_menu=0, .opt_flags=4, .opt_action=opt_act_33_0},
	{ .opt_name = "aes-cbc", .opt_menu=0, .opt_flags=4, .opt_action=opt_act_33_1},
	{ .opt_name = "3des-cbc", .opt_menu=0, .opt_flags=4, .opt_action=opt_act_33_2},
	{ .opt_name = "blowfish-cbc", .opt_menu=0, .opt_flags=4, .opt_action=opt_act_33_3}
	};

static menu_ent optent34[] = {
	{ .opt_name = "encblkno1", .opt_menu=0, .opt_flags=4, .opt_action=opt_act_34_0},
	{ .opt_name = "encblkno8", .opt_menu=0, .opt_flags=4, .opt_action=opt_act_34_1}
	};

static menu_ent optent35[] = {
	{ .opt_name = "pkcs5_pbkdf2/sha1", .opt_menu=0, .opt_flags=4, .opt_action=opt_act_35_0},
	{ .opt_name = "pkcs5_pbkdf2", .opt_menu=0, .opt_flags=4, .opt_action=opt_act_35_1},
	{ .opt_name = "storedkey", .opt_menu=0, .opt_flags=4, .opt_action=opt_act_35_2},
	{ .opt_name = "randomkey", .opt_menu=0, .opt_flags=4, .opt_action=opt_act_35_3},
	{ .opt_name = "urandomkey", .opt_menu=0, .opt_flags=4, .opt_action=opt_act_35_4},
	{ .opt_name = "shell_cmd", .opt_menu=0, .opt_flags=4, .opt_action=opt_act_35_5}
	};

static menu_ent optent36[] = {
	{ .opt_name = "none", .opt_menu=0, .opt_flags=4, .opt_action=opt_act_36_0},
	{ .opt_name = "disklabel", .opt_menu=0, .opt_flags=4, .opt_action=opt_act_36_1},
	{ .opt_name = "MBR", .opt_menu=0, .opt_flags=4, .opt_action=opt_act_36_2},
	{ .opt_name = "GPT", .opt_menu=0, .opt_flags=4, .opt_action=opt_act_36_3},
	{ .opt_name = "ffs", .opt_menu=0, .opt_flags=4, .opt_action=opt_act_36_4},
	{ .opt_name = "re-enter", .opt_menu=0, .opt_flags=4, .opt_action=opt_act_36_5}
	};

static menu_ent optent37[] = {
	{ .opt_name = MSG_entropy_add_manually, .opt_menu=0, .opt_flags=4, .opt_action=opt_act_37_0},
	{ .opt_name = MSG_entropy_download_seed, .opt_menu=0, .opt_flags=4, .opt_action=opt_act_37_1},
	{ .opt_name = MSG_entropy_download_raw, .opt_menu=0, .opt_flags=4, .opt_action=opt_act_37_2},
	{ .opt_name = MSG_entropy_retry, .opt_menu=0, .opt_flags=4, .opt_action=opt_act_37_3}
	};

static menu_ent optent38[] = {
	{ .opt_name = MSG_entropy_add_download_http, .opt_menu=0, .opt_flags=4, .opt_action=opt_act_38_0},
	{ .opt_name = MSG_entropy_add_download_ftp, .opt_menu=0, .opt_flags=4, .opt_action=opt_act_38_1},
	{ .opt_name = MSG_entropy_add_nfs, .opt_menu=0, .opt_flags=4, .opt_action=opt_act_38_2},
	{ .opt_name = MSG_entropy_add_local, .opt_menu=0, .opt_flags=4, .opt_action=opt_act_38_3}
	};

static menu_ent optent39[] = {
	{ .opt_name = 0, .opt_menu=0, .opt_flags=0, .opt_action=opt_act_39_0},
	{ .opt_name = 0, .opt_menu=0, .opt_flags=0, .opt_action=opt_act_39_1},
	{ .opt_name = 0, .opt_menu=0, .opt_flags=0, .opt_action=opt_act_39_2},
	{ .opt_name = MSG_cancel, .opt_menu=0, .opt_flags=4, .opt_action=opt_act_39_3}
	};

static void menu_39_legend(menudesc *menu, int opt, void *arg)
{
	switch (opt) {
	case 0:
		{src_legend(menu, MSG_Host, nfs_host);};
		break;
	case 1:
		{src_legend(menu, MSG_Base_dir, nfs_dir);};
		break;
	case 2:
		{src_legend(menu, MSG_entropy_file, entropy_file);};
		break;
	}
}

static menu_ent optent40[] = {
	{ .opt_name = 0, .opt_menu=0, .opt_flags=0, .opt_action=opt_act_40_0},
	{ .opt_name = 0, .opt_menu=0, .opt_flags=0, .opt_action=opt_act_40_1},
	{ .opt_name = 0, .opt_menu=0, .opt_flags=0, .opt_action=opt_act_40_2},
	{ .opt_name = 0, .opt_menu=0, .opt_flags=0, .opt_action=opt_act_40_3},
	{ .opt_name = 0, .opt_menu=0, .opt_flags=0, .opt_action=opt_act_40_4},
	{ .opt_name = MSG_cancel, .opt_menu=0, .opt_flags=4, .opt_action=opt_act_40_5}
	};

static void menu_40_legend(menudesc *menu, int opt, void *arg)
{
	switch (opt) {
	case 0:
		{src_legend(menu, MSG_Host,
			((struct ftpinfo*)((arg_rv*)arg)->arg)->xfer_host[
			XFER_HOST(((struct ftpinfo*)
			((arg_rv*)arg)->arg)->xfer)]);};
		break;
	case 1:
		{src_legend(menu, MSG_entropy_path_and_file, entropy_file);};
		break;
	case 2:
		{src_legend(menu, MSG_User,
			((struct ftpinfo*)((arg_rv*)arg)->arg)->user);};
		break;
	case 3:
		{src_legend(menu, MSG_Password,
		    strcmp(((struct ftpinfo*)((arg_rv*)arg)->arg)->user,
		        "ftp") == 0 ||
			((struct ftpinfo*)((arg_rv*)arg)->arg)->pass[0] == 0
			? ((struct ftpinfo*)((arg_rv*)arg)->arg)->pass
			: msg_string(MSG_hidden));};
		break;
	case 4:
		{src_legend(menu, MSG_Proxy,
		    ((struct ftpinfo*)((arg_rv*)arg)->arg)->proxy);};
		break;
	}
}

static menu_ent optent41[] = {
	{ .opt_name = 0, .opt_menu=0, .opt_flags=0, .opt_action=opt_act_41_0},
	{ .opt_name = 0, .opt_menu=0, .opt_flags=0, .opt_action=opt_act_41_1},
	{ .opt_name = 0, .opt_menu=0, .opt_flags=0, .opt_action=opt_act_41_2},
	{ .opt_name = MSG_cancel, .opt_menu=0, .opt_flags=4, .opt_action=opt_act_41_3}
	};

static void menu_41_legend(menudesc *menu, int opt, void *arg)
{
	switch (opt) {
	case 0:
		{src_legend(menu, MSG_Device, localfs_dev);};
		break;
	case 1:
		{src_legend(menu, MSG_File_system, localfs_fs);};
		break;
	case 2:
		{src_legend(menu, MSG_entropy_path_and_file, entropy_file);};
		break;
	}
}

static menu_ent optent42[] = {
	{ .opt_name = MSG_Use_normal_bootblocks, .opt_menu=0, .opt_flags=4, .opt_action=opt_act_42_0},
	{ .opt_name = MSG_Use_serial_com0, .opt_menu=0, .opt_flags=0, .opt_action=opt_act_42_1},
	{ .opt_name = MSG_Use_serial_com1, .opt_menu=0, .opt_flags=0, .opt_action=opt_act_42_2},
	{ .opt_name = MSG_Use_serial_com2, .opt_menu=0, .opt_flags=0, .opt_action=opt_act_42_3},
	{ .opt_name = MSG_Use_serial_com3, .opt_menu=0, .opt_flags=0, .opt_action=opt_act_42_4},
	{ .opt_name = MSG_serial_baud_rate, .opt_menu=43, .opt_flags=1, .opt_action=NULL},
	{ .opt_name = MSG_Use_existing_bootblocks, .opt_menu=0, .opt_flags=4, .opt_action=opt_act_42_6}
	};

static menu_ent optent43[] = {
	{ .opt_name = "9600", .opt_menu=0, .opt_flags=4, .opt_action=opt_act_43_0},
	{ .opt_name = "19200", .opt_menu=0, .opt_flags=4, .opt_action=opt_act_43_1},
	{ .opt_name = "38400", .opt_menu=0, .opt_flags=4, .opt_action=opt_act_43_2},
	{ .opt_name = "57600", .opt_menu=0, .opt_flags=4, .opt_action=opt_act_43_3},
	{ .opt_name = "115200", .opt_menu=0, .opt_flags=4, .opt_action=opt_act_43_4},
	{ .opt_name = "BIOS", .opt_menu=0, .opt_flags=4, .opt_action=opt_act_43_5}
	};

static menu_ent optent44[] = {
	{ .opt_name = MSG_This_is_the_correct_geometry, .opt_menu=0, .opt_flags=4, .opt_action=opt_act_44_0},
	{ .opt_name = MSG_Set_the_geometry_by_hand, .opt_menu=0, .opt_flags=4, .opt_action=opt_act_44_1}
	};

static menu_ent optent45[] = {
	{ .opt_name = MSG_Use_one_of_these_disks, .opt_menu=0, .opt_flags=4, .opt_action=opt_act_45_0},
	{ .opt_name = MSG_Set_the_geometry_by_hand, .opt_menu=0, .opt_flags=4, .opt_action=opt_act_45_1}
	};

static struct menudesc menu_def[] = {
	{ },
	{MSG_toggle,NULL,5,30,0,0,4,8,0,0,optent1,NULL,NULL,NULL,MSG_unchanged,NULL,NULL,NULL,NULL},
	{MSG_NetBSD_VERSION_Install_System,NULL,-1,-1,0,0,4,6,0,0,optent2,NULL,NULL,NULL,MSG_Exit_Install_System,NULL,menu_2_postact,NULL,NULL},
	{MSG_NetBSD_VERSION_Utilities,NULL,12,-1,0,0,4,7,0,0,optent3,NULL,NULL,NULL,MSG_exit_menu_generic,NULL,menu_3_postact,NULL,NULL},
	{MSG_Color_scheme,NULL,12,-1,0,0,4,4,0,0,optent4,NULL,NULL,NULL,MSG_exit_menu_generic,NULL,NULL,NULL,NULL},
	{"",NULL,-10,-1,0,0,5,2,0,0,optent5,NULL,NULL,NULL,NULL,NULL,menu_5_postact,NULL,NULL},
	{"",NULL,-10,-1,0,0,5,2,0,0,optent6,NULL,NULL,NULL,NULL,NULL,menu_6_postact,NULL,NULL},
	{"",NULL,-10,-1,0,0,13,1,0,0,optent7,NULL,NULL,NULL,NULL,NULL,menu_7_postact,NULL,NULL},
	{MSG_Choose_your_size_specifier,NULL,0,-1,0,0,133,4,0,0,optent8,NULL,NULL,NULL,NULL,NULL,menu_8_postact,NULL,NULL},
	{MSG_ptnsize_replace_existing,NULL,0,-1,0,0,133,2,0,0,optent9,NULL,NULL,NULL,NULL,NULL,menu_9_postact,NULL,NULL},
	{MSG_Select_medium,NULL,-5,-1,0,0,5,10,0,0,optent10,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL},
	{MSG_Select_your_distribution,NULL,12,-1,0,0,4,4,0,0,optent11,NULL,NULL,NULL,MSG_Abandon,NULL,menu_11_postact,NULL,NULL},
	{"",NULL,-4,0,0,70,22,12,0,0,optent12,NULL,NULL,NULL,MSG_Get_Distribution,NULL,menu_12_postact,NULL,menu_12_legend},
	{"",NULL,-4,0,0,70,22,7,0,0,optent13,NULL,NULL,NULL,MSG_Get_Distribution,NULL,menu_13_postact,NULL,menu_13_legend},
	{MSG_What_do_you_want_to_do,NULL,12,-1,0,0,5,3,0,0,optent14,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL},
	{MSG_What_do_you_want_to_do,NULL,12,-1,0,0,5,3,0,0,optent15,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL},
	{MSG_fd_type,NULL,16,-1,0,0,5,2,0,0,optent16,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL},
	{"",NULL,-4,0,0,70,22,5,0,0,optent17,NULL,NULL,NULL,MSG_Continue,NULL,menu_17_postact,NULL,menu_17_legend},
	{"",NULL,-4,0,0,70,22,6,0,0,optent18,NULL,NULL,NULL,MSG_Continue,NULL,menu_18_postact,NULL,menu_18_legend},
	{"",NULL,-4,0,0,70,22,7,0,0,optent19,NULL,NULL,NULL,MSG_Continue,NULL,menu_19_postact,NULL,menu_19_legend},
	{"",NULL,-4,0,0,70,22,5,0,0,optent20,NULL,NULL,NULL,MSG_Continue,NULL,menu_20_postact,NULL,menu_20_legend},
	{MSG_Select_DNS_server,NULL,12,-1,0,0,5,5,0,0,optent21,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL},
	{MSG_Root_shell,NULL,12,-1,0,0,21,3,0,0,optent22,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL},
	{"Zeroconf",NULL,12,-1,0,0,21,3,0,0,optent23,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL},
	{"",NULL,-4,0,0,70,22,10,0,0,optent24,NULL,NULL,NULL,MSG_Install_pkgin,NULL,menu_24_postact,NULL,menu_24_legend},
	{"",NULL,-4,0,0,70,22,9,0,0,optent25,NULL,NULL,NULL,MSG_Install_pkgsrc,NULL,menu_25_postact,NULL,menu_25_legend},
	{MSG_User_shell,NULL,12,-1,0,0,21,3,0,0,optent26,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL},
	{MSG_cvtscheme_hdr,NULL,12,-1,0,0,5,4,0,0,optent27,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL},
	{MSG_reeditpart,NULL,-10,-1,0,0,5,3,0,0,optent28,NULL,NULL,NULL,NULL,menu_28_expact,NULL,NULL,NULL},
	{"",NULL,5,50,0,0,36,8,0,0,optent29,NULL,NULL,NULL,"Exit",NULL,menu_29_postact,NULL,NULL},
	{"",NULL,5,50,0,0,36,2,0,0,optent30,NULL,NULL,NULL,"Exit",NULL,NULL,NULL,NULL},
	{"",NULL,5,50,0,0,36,7,0,0,optent31,NULL,NULL,NULL,"Exit",NULL,NULL,NULL,NULL},
	{"",NULL,12,-1,0,0,5,4,0,0,optent32,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL},
	{"",NULL,12,-1,0,0,5,4,0,0,optent33,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL},
	{"",NULL,12,-1,0,0,5,2,0,0,optent34,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL},
	{"",NULL,12,-1,0,0,5,6,0,0,optent35,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL},
	{"",NULL,12,-1,0,0,5,6,0,0,optent36,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL},
	{MSG_not_enough_entropy,NULL,-1,-1,0,0,6,4,0,0,optent37,NULL,NULL,NULL,MSG_continue_without_entropy,NULL,NULL,NULL,NULL},
	{MSG_entropy_select_file,NULL,-5,-1,0,0,4,4,0,0,optent38,NULL,NULL,NULL,MSG_cancel,NULL,NULL,NULL,NULL},
	{"",NULL,-5,0,0,70,22,4,0,0,optent39,NULL,NULL,NULL,MSG_load_entropy,NULL,NULL,NULL,menu_39_legend},
	{"",NULL,-4,0,0,70,22,6,0,0,optent40,NULL,NULL,NULL,MSG_download_entropy,NULL,NULL,NULL,menu_40_legend},
	{"",NULL,-4,0,0,70,22,4,0,0,optent41,NULL,NULL,NULL,MSG_load_entropy,NULL,menu_41_postact,NULL,menu_41_legend},
	{MSG_Bootblocks_selection,NULL,10,-1,0,0,20,7,0,0,optent42,NULL,NULL,NULL,MSG_Continue,NULL,menu_42_postact,NULL,NULL},
	{MSG_serial_baud_rate,NULL,13,40,0,0,5,6,0,0,optent43,NULL,NULL,NULL,NULL,NULL,menu_43_postact,NULL,NULL},
	{"",NULL,-1,-1,0,0,5,2,0,0,optent44,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL},
	{"",NULL,12,-1,0,0,5,2,0,0,optent45,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL},
{NULL, NULL, 0, 0, 0, 0, 0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL}};

/* __menu_initerror: initscr failed. */
void __menu_initerror (void) {

	fprintf (stderr, "Could not initialize menu system, please check "
	    "your terminal type.\n");
	exit(4);

}
/*	$NetBSD: menu_sys.def,v 1.72 2019/06/23 22:47:22 christos Exp $	*/

/*
 * Copyright 1997 Piermont Information Systems Inc.
 * All rights reserved.
 *
 * Written by Philip A. Nelson for Piermont Information Systems Inc.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. The name of Piermont Information Systems Inc. may not be used to endorse
 *    or promote products derived from this software without specific prior
 *    written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY PIERMONT INFORMATION SYSTEMS INC. ``AS IS''
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL PIERMONT INFORMATION SYSTEMS INC. BE 
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR 
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF 
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF 
 * THE POSSIBILITY OF SUCH DAMAGE.
 *
 */

/* menu_sys.defs -- Menu system standard routines. */

#include <string.h>
#include <ctype.h>

#define REQ_EXECUTE    1000
#define REQ_NEXT_ITEM  1001
#define REQ_PREV_ITEM  1002
#define REQ_REDISPLAY  1003
#define REQ_SCROLLDOWN 1004
#define REQ_SCROLLUP   1005
#define REQ_HELP       1006

/* Macros */
#define MAX(x,y) ((x)>(y)?(x):(y))
#define MIN(x,y) ((x)<(y)?(x):(y))

/* Initialization state. */
static int __menu_init = 0;
static int max_lines = 0, max_cols = 0;
#ifndef scrolltext
static const char *scrolltext = " <: page up, >: page down";
#endif

#ifdef DYNAMIC_MENUS
static int num_menus  = 0;
#define DYN_INIT_NUM 32
static menudesc **menu_list;
#define MENUS(n) (*(menu_list[n]))
#else
#define MENUS(n) (menu_def[n])
#endif

/* prototypes for in here! */
static void init_menu(menudesc *m);
static char opt_ch(menudesc *m, int op_no);
static void draw_menu(menudesc *m, void *arg);
static void process_help(menudesc *m);
static void process_req(menudesc *m, void *arg, int req);
static int menucmd(WINDOW *w);

#ifndef NULL
#define NULL 0
#endif

/* menu system processing routines */
#define mbeep() (void)fputc('\a', stderr)

static int
menucmd(WINDOW *w)
{
	int ch;

	while (TRUE) {
		ch = wgetch(w);
		
		switch (ch) {
		case '\n':
			return REQ_EXECUTE;
		case '\016':  /* Control-P */
		case KEY_DOWN:
			return REQ_NEXT_ITEM;
		case '\020':  /* Control-N */
		case KEY_UP:
			return REQ_PREV_ITEM;
		case '\014':  /* Control-L */
			return REQ_REDISPLAY;
		case '<':
		case '\010':  /* Control-H (backspace) */
		case KEY_PPAGE:
		case KEY_LEFT:
			return REQ_SCROLLUP;
		case '\026':  /* Control-V */
		case '>':
		case ' ':
		case KEY_NPAGE:
		case KEY_RIGHT:
			return REQ_SCROLLDOWN;
		case '?':
			return REQ_HELP;
		case '\033': /* esc-v is scroll down */
			ch = wgetch(w);
			if (ch == 'v')
				return REQ_SCROLLUP;
			else
				ch = 0; /* zap char so we beep */
		}
		
		if (isalpha(ch)) 
			return ch;

		mbeep();
		wrefresh(w);
	}
}

static void
init_menu(menudesc *m)
{
	int wmax;
	int hadd, wadd, exithadd;
	int i;
	int x, y, w;
	const char *title, *tp, *ep;

	x = m->x;
	y = m->y;
	w = m->w;
	wmax = 0;
	hadd = ((m->mopt & MC_NOBOX) ? 0 :
	    ((m->mopt & MC_CONTINUOUS) ? 1 : 2));
	wadd = ((m->mopt & MC_NOBOX) ? 2 : 4);
	if (!(m->mopt & MC_NOSHORTCUT))
		wadd += 3;

	title = m->title;
#ifdef MENU_EXPANDS
	if (m->exp_title)
		title = m->exp_title;
#endif
	if (title)
		title = MSG_XLAT(title);
	if (title && title[0] != 0) {
		/* Allow multiple line titles */
		for (tp = title; (ep = strchr(tp, '\n')); tp = ep + 1) {
			i = ep - tp;
			wmax = MAX(wmax, i);
			hadd++;
		}
		hadd++;
		i = strlen(tp);
		wmax = MAX(wmax, i);
		if (i != 0)
			hadd++;
	} else {
		m->title = NULL;
		title = "untitled";
	}
	exithadd = ((m->mopt & MC_NOEXITOPT) ? 0 : 1);

#ifdef MSG_DEFS_H
	if (y < 0) {
		/* put menu box below message text */
		y = -y;
		i = msg_row();
		if (i > y)
		    y = i;
	}
#endif

	/* Calculate h? h == number of visible options. */
	if (m->h == 0)
		m->h = m->numopts + exithadd;

	if (m->h > max_lines - y - hadd) {
		/* Not enough space for all the options */
		if (m->h <= 4 || !(m->mopt & (MC_SCROLL | MC_ALWAYS_SCROLL))) {
			/* move menu up screen */
			y = max_lines - hadd - m->h;
			if (y < 0)
				y = 0;
		}
		m->h = max_lines - y - hadd;
	}

	if (m->h < m->numopts + exithadd || m->mopt & MC_ALWAYS_SCROLL) {
		/* We need to add the scroll text... 
		 * The used to be a check for MC_SCROLL here, but it is
		 * fairly pointless - you just don't want the program
		 * to exit on this sort of error.
		 */
		if (m->h < 3) {
			endwin();
			(void)fprintf(stderr,
				"Window too short (m->h %d, m->numopts %d, exithadd %d, y %d, max_lines %d, hadd %d) for menu \"%.30s\"\n",
				m->h, m->numopts, exithadd, y, max_lines, hadd,
				title);
			exit(1);
		}
		hadd++;
		m->h = MIN(m->h, max_lines - y - hadd);
		i = strlen(scrolltext);
		wmax = MAX(wmax, i);
	}

	/* Calculate w? */
	if (w == 0) {
		int l;
		for (i = 0; i < m->numopts; i++) {
#ifdef MENU_EXPANDS
			tp = m->opts[i].opt_exp_name ?
			    m->opts[i].opt_exp_name :
			    MSG_XLAT(m->opts[i].opt_name);
#else
			tp = MSG_XLAT(m->opts[i].opt_name);
#endif
			if (tp == NULL)
				continue;
			l = strlen(tp);
			wmax = MAX(wmax, l);
		}
		w = wmax;
	}

	/* check and adjust for screen fit */
	if (w + wadd > max_cols) {
		endwin();
		(void)fprintf(stderr,
			"Screen too narrow (%d + %d > %d) for menu \"%s\"\n",
				w, wadd, max_cols, title);
		exit(1);

	}

	if (x == -1)
		x = (max_cols - (w + wadd)) / 2;	/* center */
	else if (x + w + wadd > max_cols)
		x = max_cols - (w + wadd);	/* right align */

	if (y == 0) {
		/* Center - rather than top */
		y = (max_lines - hadd - m->h) / 2;
	}

	/* Get the windows. */
	m->mw = newwin(m->h + hadd, w + wadd, y, x);

	if (m->mw == NULL) {
		endwin();
		(void)fprintf(stderr,
			"Could not create window (%d + %d, %d + %d, %d, %d) for menu \"%s\"\n",
			m->h, hadd, w, wadd, y, x, title);
		exit(1);
	}
	keypad(m->mw, TRUE); /* enable multi-key assembling for win */

	/* XXX is it even worth doing this right? */
	if (has_colors()) {
		wbkgd(m->mw, COLOR_PAIR(1));
		wattrset(m->mw, COLOR_PAIR(1));
	}

	if (m->mopt & MC_SUBMENU) {
		/* Keep a copy of what is on the screen under the window */
		m->sv_mw = newwin(m->h + hadd, w + wadd, y, x);
		/*
		 * cursrc contains post-doupdate() data, not post-refresh()
		 * data so we must call doupdate to ensure we save the
		 * correct data.  Avoids PR 26660.
		 */
		doupdate();
		if (m->sv_mw)
			overwrite(curscr, m->sv_mw);
	}
}

static char
opt_ch(menudesc *m, int op_no)
{
	char c;

	if (op_no == m->numopts)
		return 'x';

	if (op_no < 25) {
		c = 'a' + op_no;
		if (c >= 'x')
			c++;
	} else 
		c = 'A' + op_no - 25;
	return c;
}

static void
draw_menu_line(menudesc *m, int opt, int cury, void *arg, const char *text)
{
	int hasbox = m->mopt & MC_NOBOX ? 0 : 1;
	int noshort = (opt < m->numopts)
	    && (m->opts[opt].opt_flags & OPT_NOSHORT);

	if (m->cursel == opt) {
		mvwaddstr(m->mw, cury, hasbox, ">");
		wstandout(m->mw);
	} else
		mvwaddstr(m->mw, cury, hasbox, " ");
	if (!(m->mopt & MC_NOSHORTCUT) && !noshort)
		wprintw(m->mw, "%c: ", opt_ch(m, opt));
	else if (!(m->mopt & MC_NOSHORTCUT))
		wprintw(m->mw, "   ");

	if (!text && m->draw_line)
		m->draw_line(m, opt, arg);
	else
		waddstr(m->mw, MSG_XLAT(text));
	if (m->cursel == opt)
		wstandend(m->mw);
}

static void
draw_menu(menudesc *m, void *arg)
{
	int opt;
	int hasbox, cury, maxy;
	int tadd;
	int hasexit = (m->mopt & MC_NOEXITOPT ? 0 : 1);
	const char *tp, *ep;
	const char *title;
	
	hasbox = (m->mopt & MC_NOBOX ? 0 : 1);

	/* Clear the window */
	wclear(m->mw);

	tadd = hasbox;
	title = m->title;
#ifdef MENU_EXPANDS
	if (m->exp_title)
		title = m->exp_title;
#endif
	if (title) {
		for (tp = MSG_XLAT(title); ; tp = ep + 1) {
			ep = strchr(tp , '\n');
			mvwaddnstr(m->mw, tadd++, hasbox + 1, tp,
			    ep ? ep - tp : -1);
			if (ep == NULL || *ep == 0)
				break;
		}
		if ((m->mopt & MC_CONTINUOUS) == 0)
			tadd++;
	}

	cury = tadd;
	maxy = getmaxy(m->mw) - hasbox;
	if (m->numopts + hasexit > m->h)
		/* allow for scroll text */
		maxy--;

	if (m->cursel == -1) {
		m->cursel = m->numopts;
		if (m->h <= m->numopts)
			m->topline = m->numopts + 1 - m->h;
	}

	while (m->cursel >= m->topline + m->h)
		m->topline = MIN(m->topline + m->h,
				 m->numopts + hasexit - m->h);
	while (m->cursel < m->topline)
		m->topline = MAX(0, m->topline - m->h);

	for (opt = m->topline; opt < m->numopts; opt++) {
		if (cury >= maxy)
			break;
		draw_menu_line(m, opt, cury++, arg,
#ifdef MENU_EXPANDS
		    m->opts[opt].opt_exp_name ?
		    	m->opts[opt].opt_exp_name : m->opts[opt].opt_name
#else
		    m->opts[opt].opt_name
#endif
		    );
	}

	/* Add the exit option. */
	if (!(m->mopt & MC_NOEXITOPT)) {
		if (cury < maxy)
			draw_menu_line(m, m->numopts, cury++, arg, m->exitstr);
		else
			opt = 0;
	}

	/* Add the scroll line */
	if (opt != m->numopts || m->topline != 0)
		mvwaddstr(m->mw, cury, hasbox, scrolltext);

	/* Add the box. */
	if (!(m->mopt & MC_NOBOX))
		box(m->mw, 0, 0);

	wmove(m->mw, tadd + m->cursel - m->topline, hasbox);
	wrefresh(m->mw);
}


static void
/*ARGSUSED*/
process_help(menudesc *m)
{
	const char *help = m->helpstr;
	WINDOW *sv_curscr;
	int lineoff = 0;
	int curoff = 0;
	int again;
	int winin;

	/* Is there help? */
	if (!help) {
		mbeep();
		return;
	}
	sv_curscr = newwin(getmaxy(curscr), getmaxx(curscr), 0, 0);
	if (!sv_curscr) {
		mbeep();
		return;
	}
	/*
	 * Save screen contents so we can restore before returning.
	 * cursrc contains post-doupdate() data, not post-refresh()
	 * data so we must call doupdate to ensure we save the
	 * correct data.  Avoids PR 26660.
	 */
	doupdate();
	overwrite(curscr, sv_curscr);
	touchwin(stdscr);

	help = MSG_XLAT(help);
	/* Display the help information. */
	do {
		if (lineoff < curoff) {
			help = MSG_XLAT(m->helpstr);
			curoff = 0;
		}
		while (*help && curoff < lineoff) {
			if (*help == '\n')
				curoff++;
			help++;
		}
	
		wclear(stdscr);
		mvwaddstr(stdscr, 0, 0, 
			"Help: exit: x,  page up: u <, page down: d >");
		mvwaddstr(stdscr, 2, 0, help);
		wmove(stdscr, 1, 0);
		wrefresh(stdscr);

		do {
			winin = wgetch(stdscr);
			if (winin < KEY_MIN)
				winin = tolower(winin);
			again = 0;
			switch (winin) {
				case '<':
				case 'u':
				case KEY_UP:
				case KEY_LEFT:
				case KEY_PPAGE:
					if (lineoff)
						lineoff -= max_lines - 2;
					else
						again = 1;
					break;
				case '>':
				case 'd':
				case KEY_DOWN:
				case KEY_RIGHT:
				case KEY_NPAGE:
					if (*help)
						lineoff += max_lines - 2;
					else
						again = 1;
					break;
				case 'q':
					break;
				case 'x':
					winin = 'q';
					break;
				default:
					again = 1;
			}
			if (again)
				mbeep();
		} while (again);
	} while (winin != 'q');

	/* Restore the original screen contents */
	touchwin(sv_curscr);
	wnoutrefresh(sv_curscr);
	delwin(sv_curscr);

	/* Some code thinks that wrefresh(stdout) is a good idea... */
	wclear(stdscr);
}

#ifdef MENU_EXPANDS
static void
free_exp_menu_items(menudesc *m)
{
	int i;

	if (m->exp_title != NULL) {
		free(__UNCONST(m->exp_title));
		m->exp_title = NULL;
	}
	for (i = 0; i < m->numopts; i++) {
		if (m->opts[i].opt_exp_name != NULL) {
			free(__UNCONST(m->opts[i].opt_exp_name));
			m->opts[i].opt_exp_name = NULL;
		}
	}
}
#endif

static void
process_req(menudesc *m, void *arg, int req)
{
	int ch;
	int hasexit = (m->mopt & MC_NOEXITOPT ? 0 : 1);

	switch(req) {

	case REQ_EXECUTE:
		return;

	case REQ_NEXT_ITEM:
		ch = m->cursel;
		for (;;) {
			ch++;
			if (ch >= m->numopts + hasexit) {
				mbeep();
				return;
			}
			if (hasexit && ch == m->numopts)
				break;
			if (!(m->opts[ch].opt_flags & OPT_IGNORE))
				break;
		}
		m->cursel = ch;
		if (m->cursel >= m->topline + m->h)
			m->topline = m->cursel - m->h + 1;
		break;

	case REQ_PREV_ITEM:
		ch = m->cursel;
		for (;;) {
			if (ch <= 0) {
				mbeep();
				return;
			}
			ch--;
			if (!(m->opts[ch].opt_flags & OPT_IGNORE))
				break;
		}
		m->cursel = ch;
		if (m->cursel < m->topline)
			m->topline = m->cursel;
		break;

	case REQ_HELP:
		process_help(m);
		break;

	case REQ_REDISPLAY:
		endwin();
		doupdate();
		break;

	case REQ_SCROLLUP:
		if (m->cursel == 0) {
			mbeep();
			return;
		}
		m->topline = MAX(0, m->topline - m->h);
		m->cursel = MAX(0, m->cursel - m->h);
		wclear(m->mw);
		break;

	case REQ_SCROLLDOWN:
		if (m->cursel >= m->numopts + hasexit - 1) {
			mbeep();
			return;
		}
		m->topline = MIN(m->topline + m->h,
				 MAX(m->numopts + hasexit - m->h, 0));
		m->cursel = MIN(m->numopts + hasexit - 1, m->cursel + m->h);
		wclear(m->mw);
		break;

	default:
		ch = req;
		if (ch == 'x' && hasexit) {
			m->cursel = m->numopts;
			break;
		}
		if (m->mopt & MC_NOSHORTCUT) {
			mbeep();
			return;
		}
		if (ch > 'z')
			ch = 255;
		if (ch >= 'a') {
			if (ch > 'x')
				ch--;
			ch = ch - 'a';
		} else
			ch = 25 + ch - 'A';
		if (ch < 0 || ch >= m->numopts) {
			mbeep();
			return;
		}
		if (m->opts[ch].opt_flags & OPT_IGNORE) {
			mbeep();
			return;
		}
		m->cursel = ch;
	}

	draw_menu(m, arg);
}

int
menu_init(void)
{
	int i;

	if (__menu_init)
		return 0;

#ifdef	USER_MENU_INIT
	if (USER_MENU_INIT)
		return 1;
#endif

	if (initscr() == NULL)
		return 1;

	cbreak();
	noecho();

	/* XXX Should be configurable but it almost isn't worth it. */
	if (has_colors()) {
		start_color();
		init_pair(1, COLOR_WHITE, COLOR_BLUE);
		bkgd(COLOR_PAIR(1));
		attrset(COLOR_PAIR(1));
	}

	max_lines = getmaxy(stdscr);
	max_cols = getmaxx(stdscr);
	keypad(stdscr, TRUE);
#ifdef DYNAMIC_MENUS
	num_menus = DYN_INIT_NUM;
	while (num_menus < DYN_MENU_START)
		num_menus *= 2;
	menu_list = calloc(num_menus, sizeof *menu_list);
	if (menu_list == NULL)
		return 2;
	for (i = 0; i < DYN_MENU_START; i++)
		menu_list[i] = &menu_def[i];
#endif

	__menu_init = 1;
	return 0;
}

void
process_menu(int num, void *arg)
{
	int sel = 0;
	int req, rv;
	menu_ent *opt;

	menudesc *m;

	/* Initialize? */
	if (menu_init()) {
		__menu_initerror();
		return;
	}

	if (num < 0 || num >= num_menus)
		return;
	m = &MENUS(num);
	if (m == NULL)
		return;

	/* Default to select option 0 and display from 0, skip any
	 * disabled options at the top of the menu. */
	m->topline = 0;
	if ((m->mopt & (MC_DFLTEXIT | MC_NOEXITOPT)) == MC_DFLTEXIT) {
		m->cursel = -1;
	} else if (m->opts != NULL) {
		for (m->cursel = 0; m->cursel < m->numopts; m->cursel++)
			if ((m->opts[m->cursel].opt_flags & OPT_IGNORE) == 0)
				break;
	}

	for (;;) {
		if (isendwin())
			/* I'm not sure this is needed with netbsd's curses */
			doupdate();
#ifdef MENU_EXPANDS
		/* Expand the menu items, if needed */
		if (m->expand_act && m->mw == NULL)
			(*m->expand_act)(m, arg);
#endif

		/* Process the display action */
		if (m->post_act)
			(*m->post_act)(m, arg);
		if (m->mw == NULL)
			init_menu(m);
		draw_menu(m, arg);

		while ((req = menucmd(m->mw)) != REQ_EXECUTE)
			process_req(m, arg, req);

		sel = m->cursel;
		if (!(m->mopt & MC_NOCLEAR)) {
			wclear(m->mw);
			if (m->sv_mw)
				overwrite(m->sv_mw, m->mw);
			wnoutrefresh(m->mw);
		}

		/* Process the items */
		if (sel >= m->numopts)
			/* exit option */
			break;

		opt = &m->opts[sel];
		if (opt->opt_flags & OPT_IGNORE)
			continue;
		if (opt->opt_flags & OPT_ENDWIN)
			endwin();
		if (opt->opt_action) {
			rv = (*opt->opt_action)(m, arg);
			if (rv == -1)
				continue;
			else if (rv != 0)
				break;
		}

		if (opt->opt_menu != OPT_NOMENU) {
			if (!(opt->opt_flags & OPT_SUB)) {
				num = opt->opt_menu;
				wclear(m->mw);
				if (m->sv_mw) {
					overwrite(m->sv_mw, m->mw);
					delwin(m->sv_mw);
					m->sv_mw = NULL;
				}
				wnoutrefresh(m->mw);
				delwin(m->mw);
				m->mw = NULL;
				m = &MENUS(num);
				continue;
			}
			process_menu(opt->opt_menu, arg);
		}
		if (opt->opt_flags & OPT_EXIT)
			break;
	}

	if (m->mopt & MC_NOCLEAR) {
		wclear(m->mw);
		if (m->sv_mw)
			overwrite(m->sv_mw, m->mw);
		wnoutrefresh(m->mw);
	}

#ifdef MENU_EXPANDS
	/* Free expanded menu items, if any */
	free_exp_menu_items(m);
#endif

	/* Process the exit action */
	if (m->exit_act)
		(*m->exit_act)(m, arg);
	delwin(m->mw);
	m->mw = NULL;
	if (m->sv_mw) {
		delwin(m->sv_mw);
		m->sv_mw = NULL;
	}
}


void
set_menu_numopts(int menu, int numopts)
{

	MENUS(menu).numopts = numopts;
}

menudesc *
get_menudesc(int menu)
{
	if (menu < 0 || menu >= num_menus)
		return NULL;

	return &MENUS(menu);
}


/* Beginning of routines for dynamic menus. */

static int 
double_menus(void)
{
	menudesc **temp;
	int sz = sizeof *menu_list * num_menus;

	temp  = realloc(menu_list, sz * 2);
	if (temp == NULL)
		return 0;
	(void)memset(temp + num_menus, 0, sz);
	menu_list = temp;
	num_menus *= 2;

	return 1;
}

int
new_menu(const char *title, menu_ent *opts, int numopts, 
	int x, int y, int h, int w, int mopt,
	void (*post_act)(menudesc *, void *),
	void (*draw_line)(menudesc *, int, void *),
	void (*exit_act)(menudesc *, void *),
	const char *help, const char *exit_str)
{
	int ix;
	menudesc *m;

	/* Find free menu entry. */
	for (ix = DYN_MENU_START; ; ix++) {
		if (ix >= num_menus && !double_menus())
			return OPT_NOMENU;
		m = menu_list[ix];
		if (m == NULL) {
			m = calloc(1, sizeof *m);
			if (m == NULL)
				return OPT_NOMENU;
			menu_list[ix] = m;
			break;
		}
		if (!(m->mopt & MC_VALID))
			break;
	}

	/* Set Entries */
	m->title = title;
#ifdef MENU_EXPANDS
	m->exp_title = NULL;
#endif
	m->opts = opts;
	m->numopts = numopts;
	m->x = x;
	m->y = y;
	m->h = h;
	m->w = w;
	m->mopt = mopt | MC_VALID;
#ifdef MENU_EXPANDS
	m->expand_act = NULL;
#endif
	m->post_act = post_act;
	m->draw_line = draw_line;
	m->exit_act = exit_act;
	m->helpstr  = help;
	m->exitstr  = exit_str ? exit_str : "Exit";

	return ix;
}

void
free_menu(int menu_no)
{
	menudesc *m;

	if (menu_no < 0 || menu_no >= num_menus)
		return;

	m = menu_list[menu_no];
	if (!(m->mopt & MC_VALID))
		return;
	if (m->mw != NULL)
		delwin(m->mw);
	memset(m, 0, sizeof *m);
}
