int
width_awesomebar(Bar *bar, BarWidthArg *a)
{
	return a->max_width;
}

int
draw_awesomebar(Bar *bar, BarDrawArg *a)
{
	int n = 0, scm, remainder = 0, tabw, pad, ipad;
	unsigned int i;
	int x = a->x, w = a->w;

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
				scm = SchemeTitleSel;
			else
				scm = SchemeTitleNorm;

            pad = lrpad / 2;
            ipad = c->icon ? c->icw + ICONSPACING : 0;

			if (TEXTW(c->name) < tabw + ipad)
				pad = (tabw - TEXTW(c->name) + lrpad) / 2;

			drw_setscheme(drw, scheme[scm]);

			drw_text(drw, x, 0, tabw + (i < remainder ? 1 : 0), bh, pad + ipad, c->name, 0);

			if (ipad) {
			    drw_pic(drw, x + pad, (bh - c->ich) / 2, c->icw, c->ich, c->icon);
			}

			x += tabw + (i < remainder ? 1 : 0);
		}
	}
	return n;
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
