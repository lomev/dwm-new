int
width_awesomebar(Bar *bar, BarWidthArg *a)
{
	return a->max_width;
}

int
draw_awesomebar(Bar *bar, BarDrawArg *a)
{
	int n = 0, scm, remainder = 0, tabw, pad;
	unsigned int i;
	#if BAR_TITLE_LEFT_PAD && BAR_TITLE_RIGHT_PAD
	int x = a->x + lrpad / 2, w = a->w - lrpad;
	#elif BAR_TITLE_LEFT_PAD
	int x = a->x + lrpad / 2, w = a->w - lrpad / 2;
	#elif BAR_TITLE_RIGHT_PAD
	int x = a->x, w = a->w - lrpad / 2;
	#else
	int x = a->x, w = a->w;
	#endif // BAR_TITLE_LEFT_PAD | BAR_TITLE_RIGHT_PAD

	Client *c;
	for (c = bar->mon->clients; c; c = c->next)
		if (ISVISIBLE(c))
			n++;

	if (n > 0) {
		remainder = w % n;
		tabw = w / n;
		for (i = 0, c = bar->mon->clients; c; c = c->next, i++) {
			if (!ISVISIBLE(c))
				continue;
			if (bar->mon->sel == c)
				#if BAR_VTCOLORS_PATCH
				scm = SchemeTitleSel;
				#elif BAR_TITLECOLOR_PATCH
				scm = SchemeTitle;
				#else
				scm = SchemeSel;
				#endif // BAR_VTCOLORS_PATCH / BAR_TITLECOLOR_PATCH
			#ifdef HIDDEN
			else if (HIDDEN(c))
				scm = SchemeHid;
			#endif
			else
				#if BAR_VTCOLORS_PATCH
				scm = SchemeTitleNorm;
				#else
				scm = SchemeNorm;
				#endif // BAR_VTCOLORS_PATCH

			pad = lrpad / 2;
			#if BAR_CENTEREDWINDOWNAME_PATCH
			if (TEXTW(c->name) < tabw)
				pad = (tabw - TEXTW(c->name) + lrpad) / 2;
			#endif // BAR_CENTEREDWINDOWNAME_PATCH

			drw_setscheme(drw, scheme[scm]);
			#if BAR_PANGO_PATCH
			drw_text(drw, x, 0, tabw + (i < remainder ? 1 : 0), bh, pad, c->name, 0, False);
			#else
			drw_text(drw, x, 0, tabw + (i < remainder ? 1 : 0), bh, pad, c->name, 0);
			#endif // BAR_PANGO_PATCH
			x += tabw + (i < remainder ? 1 : 0);
		}
	}
	return a->x + a->w;
}

int
click_awesomebar(Bar *bar, Arg *arg, BarClickArg *a)
{
	int x = 0, n = 0;
	Client *c;

	for (c = bar->mon->clients; c; c = c->next)
		if (ISVISIBLE(c))
			n++;

	c = bar->mon->clients;

	do {
		if (!c || !ISVISIBLE(c))
			continue;
		else
			x += (1.0 / (double)n) * a->rel_w;
	} while (c && a->rel_x > x && (c = c->next));

	if (c) {
		arg->v = c;
		return ClkWinTitle;
	}
	return -1;
}