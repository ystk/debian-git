#include "string-list.h"
#include "argv-array.h"
static int diff_use_color_default = -1;
static int diff_context_default = 3;
static const char *diff_order_file_cfg;
static long diff_algorithm;
static int parse_diff_color_slot(const char *var)
	if (!strcasecmp(var, "plain"))
	if (!strcasecmp(var, "meta"))
	if (!strcasecmp(var, "frag"))
	if (!strcasecmp(var, "old"))
	if (!strcasecmp(var, "new"))
	if (!strcasecmp(var, "commit"))
	if (!strcasecmp(var, "whitespace"))
	if (!strcasecmp(var, "func"))
static int parse_dirstat_params(struct diff_options *options, const char *params_string,
	char *params_copy = xstrdup(params_string);
	struct string_list params = STRING_LIST_INIT_NODUP;
	int ret = 0;
	int i;
	if (*params_copy)
		string_list_split_in_place(&params, params_copy, ',', -1);
	for (i = 0; i < params.nr; i++) {
		const char *p = params.items[i].string;
		if (!strcmp(p, "changes")) {
		} else if (!strcmp(p, "lines")) {
		} else if (!strcmp(p, "files")) {
		} else if (!strcmp(p, "noncumulative")) {
		} else if (!strcmp(p, "cumulative")) {
			if (!*end)
				strbuf_addf(errmsg, _("  Failed to parse dirstat cut-off percentage '%s'\n"),
					    p);
			strbuf_addf(errmsg, _("  Unknown dirstat parameter '%s'\n"), p);
	string_list_clear(&params, 0);
	free(params_copy);
static int parse_submodule_params(struct diff_options *options, const char *value)
{
	if (!strcmp(value, "log"))
		DIFF_OPT_SET(options, SUBMODULE_LOG);
	else if (!strcmp(value, "short"))
		DIFF_OPT_CLR(options, SUBMODULE_LOG);
	else
		return -1;
	return 0;
}

long parse_algorithm_value(const char *value)
{
	if (!value)
		return -1;
	else if (!strcasecmp(value, "myers") || !strcasecmp(value, "default"))
		return 0;
	else if (!strcasecmp(value, "minimal"))
		return XDF_NEED_MINIMAL;
	else if (!strcasecmp(value, "patience"))
		return XDF_PATIENCE_DIFF;
	else if (!strcasecmp(value, "histogram"))
		return XDF_HISTOGRAM_DIFF;
	return -1;
}

	if (!strcmp(var, "diff.context")) {
		diff_context_default = git_config_int(var, value);
		if (diff_context_default < 0)
			return -1;
		return 0;
	}
	if (!strcmp(var, "diff.orderfile"))
		return git_config_pathname(&diff_order_file_cfg, var, value);
	if (!strcmp(var, "diff.submodule")) {
		if (parse_submodule_params(&default_diff_options, value))
			warning(_("Unknown value for 'diff.submodule' config variable: '%s'"),
				value);
		return 0;
	}

	if (!strcmp(var, "diff.algorithm")) {
		diff_algorithm = parse_algorithm_value(value);
		if (diff_algorithm < 0)
			return -1;
		return 0;
	}

	const char *name;

	if (skip_prefix(var, "diff.color.", &name) ||
	    skip_prefix(var, "color.diff.", &name)) {
		int slot = parse_diff_color_slot(name);
	if (starts_with(var, "submodule."))
	fputs(diff_line_prefix(o), file);
	strbuf_addstr(&msgbuf, frag);
	strbuf_addstr(&msgbuf, reset);
		strbuf_addstr(&msgbuf, plain);
		strbuf_addstr(&msgbuf, reset);
		strbuf_addstr(&msgbuf, func);
		strbuf_addstr(&msgbuf, reset);
		putc('\n', ecb->opt->file);
	const char *line_prefix = diff_line_prefix(o);
	ecbdata.ws_rule = whitespace_rule(name_b);
	const char *line_prefix;
	line_prefix = diff_line_prefix(opt);
	const char *line_prefix;
	line_prefix = diff_line_prefix(opt);
const char *diff_line_prefix(struct diff_options *opt)
{
	struct strbuf *msgbuf;
	if (!opt->output_prefix)
		return "";

	msgbuf = opt->output_prefix(opt, opt->output_prefix_data);
	return msgbuf->buf;
}

	const char *line_prefix = diff_line_prefix(o);
		} else if (starts_with(line, "\\ ")) {
	int pfx_adjust_for_slash;
	/*
	 * If there is a common prefix, it must end in a slash.  In
	 * that case we let this loop run 1 into the prefix to see the
	 * same slash.
	 *
	 * If there is no common prefix, we cannot do this as it would
	 * underrun the input strings.
	 */
	pfx_adjust_for_slash = (pfx_length ? 1 : 0);
	while (a + pfx_length - pfx_adjust_for_slash <= old &&
	       b + pfx_length - pfx_adjust_for_slash <= new &&
	       *old == *new) {
		unsigned is_interesting:1;
	x = xcalloc(1, sizeof(*x));
	ALLOC_GROW(diffstat->files, diffstat->nr + 1, diffstat->alloc);
		return fprintf(fp, "%s\n", " 0 files changed");
		    (files == 1) ? " %d file changed" : " %d files changed",
			    (insertions == 1) ? ", %d insertion(+)" : ", %d insertions(+)",
			    (deletions == 1) ? ", %d deletion(-)" : ", %d deletions(-)",
	int total_files = data->nr, count;
	int width, name_width, graph_width, number_width = 0, bin_width = 0;
	line_prefix = diff_line_prefix(options);

		if (!file->is_interesting && (change == 0)) {
		if (file->is_unmerged) {
			/* "Unmerged" is 8 characters */
			bin_width = bin_width < 8 ? 8 : bin_width;
			continue;
		}
		if (file->is_binary) {
			/* "Bin XXX -> YYY bytes" */
			int w = 14 + decimal_width(file->added)
				+ decimal_width(file->deleted);
			bin_width = bin_width < w ? w : bin_width;
			/* Display change counts aligned with "Bin" */
			number_width = 3;
		}

	count = i; /* where we can stop scanning in data->files[] */
	 *
	 * Binary files are displayed with "Bin XXX -> YYY bytes"
	 * instead of the change count and graph. This part is treated
	 * similarly to the graph part, except that it is not
	 * "scaled". If total width is too small to accommodate the
	 * guaranteed minimum width of the filename part and the
	 * separators and this message, this message will "overflow"
	 * making the line longer than the maximum width.
	number_width = decimal_width(max_change) > number_width ?
		decimal_width(max_change) : number_width;
	 * strlen("Bin XXX -> YYY bytes") == bin_width, and the part
	 * starting from "XXX" should fit in graph_width.
	graph_width = max_change + 4 > bin_width ? max_change : bin_width - 4;
	if (options->stat_graph_width &&
	    options->stat_graph_width < graph_width)
		graph_width = options->stat_graph_width;

		struct diffstat_file *file = data->files[i];
		char *name = file->print_name;
		uintmax_t added = file->added;
		uintmax_t deleted = file->deleted;
		if (!file->is_interesting && (added + deleted == 0))

		if (file->is_binary) {
			fprintf(options->file, " %*s", number_width, "Bin");
			if (!added && !deleted) {
				putc('\n', options->file);
				continue;
			}
			fprintf(options->file, " %s%"PRIuMAX"%s",
		else if (file->is_unmerged) {
			fprintf(options->file, " Unmerged\n");
			int total = scale_linear(add + del, graph_width, max_change);
		fprintf(options->file, " %*"PRIuMAX"%s",
			number_width, added + deleted,
			added + deleted ? " " : "");

	for (i = 0; i < data->nr; i++) {
		struct diffstat_file *file = data->files[i];
		uintmax_t added = file->added;
		uintmax_t deleted = file->deleted;

		if (file->is_unmerged ||
		    (!file->is_interesting && (added + deleted == 0))) {

		if (!file->is_binary) {
			adds += added;
			dels += deleted;
		}
		if (i < count)
			continue;
		int added = data->files[i]->added;
		int deleted= data->files[i]->deleted;

		if (data->files[i]->is_unmerged ||
		    (!data->files[i]->is_interesting && (added + deleted == 0))) {
			total_files--;
		} else if (!data->files[i]->is_binary) { /* don't count bytes */
			adds += added;
			dels += deleted;
	fprintf(options->file, "%s", diff_line_prefix(options));
		fprintf(options->file, "%s", diff_line_prefix(options));
	const char *line_prefix = diff_line_prefix(opt);
	const char *line_prefix;
	line_prefix = diff_line_prefix(data->o);
static void emit_binary_diff_body(FILE *file, mmfile_t *one, mmfile_t *two,
				  const char *prefix)
static void emit_binary_diff(FILE *file, mmfile_t *one, mmfile_t *two,
			     const char *prefix)
	const char *meta = diff_get_color_opt(o, DIFF_METAINFO);
	const char *line_prefix = diff_line_prefix(o);
		show_submodule_summary(o->file, one->path ? one->path : two->path,
				line_prefix,
				meta, del, add, reset);
	strbuf_addf(&header, "%s%sdiff --git %s %s%s\n", line_prefix, meta, a_one, b_two, reset);
		strbuf_addf(&header, "%s%snew file mode %06o%s\n", line_prefix, meta, two->mode, reset);
		strbuf_addf(&header, "%s%sdeleted file mode %06o%s\n", line_prefix, meta, one->mode, reset);
			strbuf_addf(&header, "%s%sold mode %06o%s\n", line_prefix, meta, one->mode, reset);
			strbuf_addf(&header, "%s%snew mode %06o%s\n", line_prefix, meta, two->mode, reset);
		const char *v;
		ecbdata.ws_rule = whitespace_rule(name_b);
		else if (skip_prefix(diffopts, "--unified=", &v))
			xecfg.ctxlen = strtoul(v, NULL, 10);
		else if (skip_prefix(diffopts, "-u", &v))
			xecfg.ctxlen = strtoul(v, NULL, 10);
			     struct diff_filepair *p)
	int same_contents;
	int complete_rewrite = 0;

	if (!DIFF_PAIR_UNMERGED(p)) {
		if (p->status == DIFF_STATUS_MODIFIED && p->score)
			complete_rewrite = 1;
	}
	data->is_interesting = p->status != DIFF_STATUS_UNKNOWN;
	same_contents = !hashcmp(one->sha1, two->sha1);

		if (same_contents) {
			data->added = 0;
			data->deleted = 0;
		} else {
			data->added = diff_filespec_size(two);
			data->deleted = diff_filespec_size(one);
		}
	else if (!same_contents) {
		   int sha1_valid, unsigned short mode)
		spec->sha1_valid = sha1_valid;
	const struct cache_entry *ce;
	/*
	 * demote FAIL to WARN to allow inspecting the situation
	 * instead of refusing.
	 */
	enum safe_crlf crlf_warn = (safe_crlf == SAFE_CRLF_FAIL
				    ? SAFE_CRLF_WARN
				    : safe_crlf);

		if (convert_to_git(s->path, s->data, s->size, &buf, crlf_warn)) {
	if (!S_ISGITLINK(one->mode) &&
	    (!one->sha1_valid ||
	     reuse_worktree_file(name, one->sha1, 1))) {
static void add_external_diff_name(struct argv_array *argv,
				   const char *name,
				   struct diff_filespec *df)
{
	struct diff_tempfile *temp = prepare_temp_file(name, df);
	argv_array_push(argv, temp->name);
	argv_array_push(argv, temp->hex);
	argv_array_push(argv, temp->mode);
}

			      int complete_rewrite,
			      struct diff_options *o)
	struct argv_array argv = ARGV_ARRAY_INIT;
	struct argv_array env = ARGV_ARRAY_INIT;
	struct diff_queue_struct *q = &diff_queued_diff;

	argv_array_push(&argv, pgm);
	argv_array_push(&argv, name);
		add_external_diff_name(&argv, name, one);
		if (!other)
			add_external_diff_name(&argv, name, two);
		else {
			add_external_diff_name(&argv, other, two);
			argv_array_push(&argv, other);
			argv_array_push(&argv, xfrm_msg);

	argv_array_pushf(&env, "GIT_DIFF_PATH_COUNTER=%d", ++o->diff_path_counter);
	argv_array_pushf(&env, "GIT_DIFF_PATH_TOTAL=%d", q->nr);

	if (run_command_v_opt_cd_env(argv.argv, RUN_USING_SHELL, NULL, env.argv))
		die(_("external diff died, stopping at %s"), name);

	argv_array_clear(&argv);
	argv_array_clear(&env);
	const char *line_prefix = diff_line_prefix(o);

	if (DIFF_OPT_TST(o, ALLOW_EXTERNAL)) {
				  complete_rewrite, o);
			if (one->is_stdin) {
	if (!DIFF_OPT_TST(o, ALLOW_EXTERNAL))
		pgm = NULL;

		builtin_diffstat(p->one->path, NULL, NULL, NULL, diffstat, o, p);
	builtin_diffstat(name, other, p->one, p->two, diffstat, o, p);
	options->context = diff_context_default;
	/* pathchange left =NULL by default */
	options->xdl_opts |= diff_algorithm;

	options->orderfile = diff_order_file_cfg;
void diff_setup_done(struct diff_options *options)
	if (options->set_default)
		options->set_default(options);

	options->diff_path_counter = 0;

	if (DIFF_OPT_TST(options, FOLLOW_RENAMES) && options->pathspec.nr != 1)
		die(_("--follow requires exactly one pathspec"));
	eq = strchrnul(arg, '=');
	len = eq - arg;
	if (*eq) {
	if (!skip_prefix(arg, "--", &arg))
	if (!skip_prefix(arg, opt, &arg))
	if (*arg == '=') { /* stuck form: --option=value */
	if (!skip_prefix(arg, "--stat", &arg))
		die("BUG: stat option does not begin with --stat: %s", arg);
		if (skip_prefix(arg, "-width", &arg)) {
		} else if (skip_prefix(arg, "-name-width", &arg)) {
		} else if (skip_prefix(arg, "-graph-width", &arg)) {
		} else if (skip_prefix(arg, "-count", &arg)) {
static int parse_submodule_opt(struct diff_options *options, const char *value)
{
	if (parse_submodule_params(options, value))
		die(_("Failed to parse --submodule option parameter: '%s'"),
			value);
	return 1;
}

static const char diff_status_letters[] = {
	DIFF_STATUS_ADDED,
	DIFF_STATUS_COPIED,
	DIFF_STATUS_DELETED,
	DIFF_STATUS_MODIFIED,
	DIFF_STATUS_RENAMED,
	DIFF_STATUS_TYPE_CHANGED,
	DIFF_STATUS_UNKNOWN,
	DIFF_STATUS_UNMERGED,
	DIFF_STATUS_FILTER_AON,
	DIFF_STATUS_FILTER_BROKEN,
	'\0',
};

static unsigned int filter_bit['Z' + 1];

static void prepare_filter_bits(void)
{
	int i;

	if (!filter_bit[DIFF_STATUS_ADDED]) {
		for (i = 0; diff_status_letters[i]; i++)
			filter_bit[(int) diff_status_letters[i]] = (1 << i);
	}
}

static unsigned filter_bit_tst(char status, const struct diff_options *opt)
{
	return opt->filter & filter_bit[(int) status];
}

static int parse_diff_filter_opt(const char *optarg, struct diff_options *opt)
{
	int i, optch;

	prepare_filter_bits();

	/*
	 * If there is a negation e.g. 'd' in the input, and we haven't
	 * initialized the filter field with another --diff-filter, start
	 * from full set of bits, except for AON.
	 */
	if (!opt->filter) {
		for (i = 0; (optch = optarg[i]) != '\0'; i++) {
			if (optch < 'a' || 'z' < optch)
				continue;
			opt->filter = (1 << (ARRAY_SIZE(diff_status_letters) - 1)) - 1;
			opt->filter &= ~filter_bit[DIFF_STATUS_FILTER_AON];
			break;
		}
	}

	for (i = 0; (optch = optarg[i]) != '\0'; i++) {
		unsigned int bit;
		int negate;

		if ('a' <= optch && optch <= 'z') {
			negate = 1;
			optch = toupper(optch);
		} else {
			negate = 0;
		}

		bit = (0 <= optch && optch <= 'Z') ? filter_bit[optch] : 0;
		if (!bit)
			return optarg[i];
		if (negate)
			opt->filter &= ~bit;
		else
			opt->filter |= bit;
	}
	return 0;
}

static void enable_patch_output(int *fmt) {
	*fmt &= ~DIFF_FORMAT_NO_OUTPUT;
	*fmt |= DIFF_FORMAT_PATCH;
}

	if (!strcmp(arg, "-p") || !strcmp(arg, "-u") || !strcmp(arg, "--patch")
	    || opt_arg(arg, 'U', "unified", &options->context))
		enable_patch_output(&options->output_format);
	else if (!strcmp(arg, "--patch-with-raw")) {
		enable_patch_output(&options->output_format);
		options->output_format |= DIFF_FORMAT_RAW;
	} else if (!strcmp(arg, "--numstat"))
	else if (skip_prefix(arg, "-X", &arg))
		return parse_dirstat_opt(options, arg);
	else if (skip_prefix(arg, "--dirstat=", &arg))
		return parse_dirstat_opt(options, arg);
	else if (skip_prefix(arg, "--dirstat-by-file=", &arg)) {
		return parse_dirstat_opt(options, arg);
	else if (!strcmp(arg, "--patch-with-stat")) {
		enable_patch_output(&options->output_format);
		options->output_format |= DIFF_FORMAT_DIFFSTAT;
	} else if (!strcmp(arg, "--name-only"))
	else if (!strcmp(arg, "-s") || !strcmp(arg, "--no-patch"))
	else if (starts_with(arg, "--stat"))
	else if (starts_with(arg, "-B") || starts_with(arg, "--break-rewrites=") ||
	else if (starts_with(arg, "-M") || starts_with(arg, "--find-renames=") ||
	else if (starts_with(arg, "-C") || starts_with(arg, "--find-copies=") ||
	else if (skip_prefix(arg, "--relative=", &arg)) {
		options->prefix = arg;
	else if (!strcmp(arg, "--ignore-blank-lines"))
		DIFF_XDL_SET(options, IGNORE_BLANK_LINES);
	else if ((argcount = parse_long_opt("diff-algorithm", av, &optarg))) {
		long value = parse_algorithm_value(optarg);
		if (value < 0)
			return error("option diff-algorithm accepts \"myers\", "
				     "\"minimal\", \"patience\" and \"histogram\"");
		/* clear out previous settings */
		DIFF_XDL_CLR(options, NEED_MINIMAL);
		options->xdl_opts &= ~XDF_DIFF_ALGORITHM_MASK;
		options->xdl_opts |= value;
		return argcount;
	}
		enable_patch_output(&options->output_format);
	else if (!strcmp(arg, "--no-follow"))
		DIFF_OPT_CLR(options, FOLLOW_RENAMES);
	else if (skip_prefix(arg, "--color=", &arg)) {
		int value = git_config_colorbool(NULL, arg);
	else if (skip_prefix(arg, "--color-words=", &arg)) {
		options->word_regex = arg;
	else if (skip_prefix(arg, "--word-diff=", &arg)) {
		if (!strcmp(arg, "plain"))
		else if (!strcmp(arg, "color")) {
		else if (!strcmp(arg, "porcelain"))
		else if (!strcmp(arg, "none"))
			die("bad --word-diff argument: %s", arg);
	} else if (skip_prefix(arg, "--ignore-submodules=", &arg)) {
		handle_ignore_submodules_arg(options, arg);
	else if (skip_prefix(arg, "--submodule=", &arg))
		return parse_submodule_opt(options, arg);
		int offending = parse_diff_filter_opt(optarg, options);
		if (offending)
			die("unknown change class '%c' in --diff-filter=%s",
			    offending, optarg);
	else if (skip_prefix(arg, "--abbrev=", &arg)) {
		options->abbrev = strtoul(arg, NULL, 10);
		if (skip_prefix(opt, "break-rewrites", &opt)) {
		} else if (skip_prefix(opt, "find-copies", &opt)) {
		} else if (skip_prefix(opt, "find-renames", &opt)) {
		return -1; /* that is not a -M, -C, or -B option */
	ALLOC_GROW(queue->queue, queue->nr + 1, queue->alloc);
	fprintf(opt->file, "%s", diff_line_prefix(opt));
	fprintf(stderr, "queue[%d] %s size %lu\n",
		s->size);
	const char *line_prefix = diff_line_prefix(opt);
	if (starts_with(line, "@@ -"))
		 * options->file to /dev/null should be safe, because we
			fprintf(options->file, "%s%c",
				diff_line_prefix(options),
				options->line_termination);
static int match_filter(const struct diff_options *options, const struct diff_filepair *p)
{
	return (((p->status == DIFF_STATUS_MODIFIED) &&
		 ((p->score &&
		   filter_bit_tst(DIFF_STATUS_FILTER_BROKEN, options)) ||
		  (!p->score &&
		   filter_bit_tst(DIFF_STATUS_MODIFIED, options)))) ||
		((p->status != DIFF_STATUS_MODIFIED) &&
		 filter_bit_tst(p->status, options)));
}

static void diffcore_apply_filter(struct diff_options *options)

	if (!options->filter)
	if (filter_bit_tst(DIFF_STATUS_FILTER_AON, options)) {
			if (match_filter(options, q->queue[i]))
			if (match_filter(options, p))
static int diff_filespec_check_stat_unmatch(struct diff_filepair *p)
{
	if (p->done_skip_stat_unmatch)
		return p->skip_stat_unmatch_result;

	p->done_skip_stat_unmatch = 1;
	p->skip_stat_unmatch_result = 0;
	/*
	 * 1. Entries that come from stat info dirtiness
	 *    always have both sides (iow, not create/delete),
	 *    one side of the object name is unknown, with
	 *    the same mode and size.  Keep the ones that
	 *    do not match these criteria.  They have real
	 *    differences.
	 *
	 * 2. At this point, the file is known to be modified,
	 *    with the same mode and size, and the object
	 *    name of one side is unknown.  Need to inspect
	 *    the identical contents.
	 */
	if (!DIFF_FILE_VALID(p->one) || /* (1) */
	    !DIFF_FILE_VALID(p->two) ||
	    (p->one->sha1_valid && p->two->sha1_valid) ||
	    (p->one->mode != p->two->mode) ||
	    diff_populate_filespec(p->one, 1) ||
	    diff_populate_filespec(p->two, 1) ||
	    (p->one->size != p->two->size) ||
	    !diff_filespec_is_identical(p->one, p->two)) /* (2) */
		p->skip_stat_unmatch_result = 1;
	return p->skip_stat_unmatch_result;
}

		if (diff_filespec_check_stat_unmatch(p))
	/* NOTE please keep the following in sync with diff_tree_combined() */
	diffcore_apply_filter(options);
	diff_warn_rename_limit("diff.renameLimit",
		    int sha1_valid,
		fill_filespec(one, sha1, sha1_valid, mode);
		fill_filespec(two, sha1, sha1_valid, mode);
		 int old_sha1_valid, int new_sha1_valid,
	struct diff_filepair *p;
		tmp = old_sha1_valid; old_sha1_valid = new_sha1_valid;
			new_sha1_valid = tmp;
	fill_filespec(one, old_sha1, old_sha1_valid, old_mode);
	fill_filespec(two, new_sha1, new_sha1_valid, new_mode);
	p = diff_queue(&diff_queued_diff, one, two);
	if (DIFF_OPT_TST(options, DIFF_FROM_CONTENTS))
		return;

	if (DIFF_OPT_TST(options, QUICK) && options->skip_stat_unmatch &&
	    !diff_filespec_check_stat_unmatch(p))
		return;

	DIFF_OPT_SET(options, HAS_CHANGES);

void setup_diff_pager(struct diff_options *opt)
{
	/*
	 * If the user asked for our exit code, then either they want --quiet
	 * or --exit-code. We should definitely not bother with a pager in the
	 * former case, as we will generate no output. Since we still properly
	 * report our exit code even when a pager is run, we _could_ run a
	 * pager with --exit-code. But since we have not done so historically,
	 * and because it is easy to find people oneline advising "git diff
	 * --exit-code" in hooks and other scripts, we do not do so.
	 */
	if (!DIFF_OPT_TST(opt, EXIT_WITH_STATUS) &&
	    check_pager_config("diff") != 0)
		setup_pager();
}