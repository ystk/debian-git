#include "xdiff-interface.h"
#include "ll-merge.h"
#include "rerere.h"
static int threeway;
	N_("git apply [options] [<patch>...]"),
	die(_("unrecognized whitespace option '%s'"), option);
	die(_("unrecognized whitespace ignore option '%s'"), option);
	/*
	 * 'patch' is usually borrowed from buf in apply_patch(),
	 * but some codepaths store an allocated buffer.
	 */
	unsigned free_patch:1,
		rejected:1;
	unsigned int conflicted_threeway:1;
	unsigned int direct_to_threeway:1;

	/* three-way fallback result */
	unsigned char threeway_stage[3][20];
static void free_fragment_list(struct fragment *list)
{
	while (list) {
		struct fragment *next = list->next;
		if (list->free_patch)
			free((char *)list->patch);
		free(list);
		list = next;
	}
}

static void free_patch(struct patch *patch)
{
	free_fragment_list(patch->fragments);
	free(patch->def_name);
	free(patch->old_name);
	free(patch->new_name);
	free(patch->result);
	free(patch);
}

static void free_patch_list(struct patch *list)
{
	while (list) {
		struct patch *next = list->next;
		free_patch(list);
		list = next;
	}
}

	/* skip leading whitespaces, if both begin with whitespace */
	if (s1 <= last1 && s2 <= last2 && isspace(*s1) && isspace(*s2)) {
		while (isspace(*s1) && (s1 <= last1))
			s1++;
		while (isspace(*s2) && (s2 <= last2))
			s2++;
	}
/*
 * "buf" has the file contents to be patched (read from various sources).
 * attach it to "image" and add line-based index to it.
 * "image" now owns the "buf".
 */
	free(image->line_allocated);
	memset(image, 0, sizeof(*image));
/* fmt must contain _one_ %s and no other substitution */
static void say_patch_name(FILE *output, const char *fmt, struct patch *patch)
	struct strbuf sb = STRBUF_INIT;

		quote_c_style(patch->old_name, &sb, NULL, 0);
		strbuf_addstr(&sb, " => ");
		quote_c_style(patch->new_name, &sb, NULL, 0);
		quote_c_style(n, &sb, NULL, 0);
	fprintf(output, fmt, sb.buf);
	fputc('\n', output);
	strbuf_release(&sb);
static char *find_name_gnu(const char *line, const char *def, int p_value)
	 * http://marc.info/?l=git&m=112927316408690&w=2
static char *null_strdup(const char *s)
{
	return s ? xstrdup(s) : NULL;
}

static char *find_name_common(const char *line, const char *def,
			      int p_value, const char *end, int terminate)
		return squash_slash(null_strdup(def));
		return squash_slash(null_strdup(def));
			return squash_slash(xstrdup(def));
	size_t len;
			warning(_("Cannot prepare timestamp regexp %s"),
			warning(_("regexec returned %d for input: %s"),
		char *first_name;
		first_name = find_name_traditional(first, NULL, p_value);
		name = find_name_traditional(second, first_name, p_value);
		free(first_name);
			patch->old_name = name;
			patch->new_name = null_strdup(name);
		die(_("unable to find filename in patch at line %d"), linenr);
#define DIFF_OLD_NAME 0
#define DIFF_NEW_NAME 1

static char *gitdiff_verify_name(const char *line, int isnull, char *orig_name, int side)
			die(_("git apply: bad git-diff - expected /dev/null, got %s on line %d"), name, linenr);
			die((side == DIFF_NEW_NAME) ?
			    _("git apply: bad git-diff - inconsistent new filename on line %d") :
			    _("git apply: bad git-diff - inconsistent old filename on line %d"), linenr);
			die(_("git apply: bad git-diff - expected /dev/null on line %d"), linenr);
	char *orig = patch->old_name;
	patch->old_name = gitdiff_verify_name(line, patch->is_new, patch->old_name,
					      DIFF_OLD_NAME);
	if (orig != patch->old_name)
		free(orig);
	char *orig = patch->new_name;
	patch->new_name = gitdiff_verify_name(line, patch->is_delete, patch->new_name,
					      DIFF_NEW_NAME);
	if (orig != patch->new_name)
		free(orig);
	free(patch->old_name);
	patch->old_name = null_strdup(patch->def_name);
	free(patch->new_name);
	patch->new_name = null_strdup(patch->def_name);
	free(patch->old_name);
	free(patch->new_name);
	free(patch->old_name);
	free(patch->new_name);
	unsigned long val = strtoul(line, NULL, 10);
	if (val <= 100)
		patch->score = val;
	unsigned long val = strtoul(line, NULL, 10);
	if (val <= 100)
		patch->score = val;
	eol = strchrnul(line, '\n');
/*
 * Skip p_value leading components from "line"; as we do not accept
 * absolute paths, return NULL in that case.
 */
static const char *skip_tree_prefix(const char *line, int llen)
	int nslash;
	if (!p_value)
		return (llen && line[0] == '/') ? NULL : line;

	nslash = p_value;
			return (i == 0) ? NULL : &line[i + 1];
static char *git_header_name(const char *line, int llen)
		/* strip the a/b prefix including trailing slash */
		cp = skip_tree_prefix(first.buf, first.len);
		if (!cp)
		strbuf_remove(&first, 0, cp - first.buf);
			cp = skip_tree_prefix(sp.buf, sp.len);
			if (!cp)
			if (strcmp(cp, first.buf))
		cp = skip_tree_prefix(second, line + llen - second);
		if (!cp)
		if (line + llen - cp != first.len ||
	name = skip_tree_prefix(line, llen);
	if (!name)
			np = skip_tree_prefix(sp.buf, sp.len);
			if (!np)
			/*
			 * Is this the separator between the preimage
			 * and the postimage pathname?  Again, we are
			 * only interested in the case where there is
			 * no rename, as this is only to set def_name
			 * and a rename patch has the names elsewhere
			 * in an unambiguous form.
			 */
			if (!name[len + 1])
				return NULL; /* no postimage name */
			second = skip_tree_prefix(name + len + 1,
						  line_len - (len + 1));
			/*
			 * Does len bytes starting at "name" and "second"
			 * (that are separated by one HT or SP we just
			 * found) exactly match?
			 */
			if (second[len] == '\n' && !strncmp(name, second, len))
static int parse_git_header(const char *line, int len, unsigned int size, struct patch *patch)
		char *s = xstrfmt("%s%s", root, patch->def_name);
static void recount_diff(const char *line, int size, struct fragment *fragment)
			ret = size < 3 || !starts_with(line, "@@ ");
			ret = size < 5 || !starts_with(line, "diff ");
			warning(_("recount: unexpected line: %.*s"),
static int parse_fragment_header(const char *line, int len, struct fragment *fragment)
static int find_header(const char *line, unsigned long size, int *hdrsize, struct patch *patch)
			die(_("patch fragment without header at line %d: %.*s"),
					die(Q_("git diff header lacks filename information when removing "
					       "%d leading pathname component (line %d)",
					       "git diff header lacks filename information when removing "
					       "%d leading pathname components (line %d)",
					       p_value),
					    p_value, linenr);
				patch->old_name = xstrdup(patch->def_name);
				patch->new_name = xstrdup(patch->def_name);
static int parse_fragment(const char *line, unsigned long size,
		return error(_("new file depends on old contents"));
		return error(_("deleted file still has contents"));
/*
 * We have seen "diff --git a/... b/..." header (or a traditional patch
 * header).  Read hunks that belong to this patch into fragments and hang
 * them to the given patch structure.
 *
 * The (fragment->patch, fragment->size) pair points into the memory given
 * by the caller, not a copy, when we return.
 */
static int parse_single_patch(const char *line, unsigned long size, struct patch *patch)
			die(_("corrupt patch at line %d"), linenr);
		die(_("new file %s depends on old contents"), patch->new_name);
		die(_("deleted file %s still has contents"), patch->old_name);
		fprintf_ln(stderr,
			   _("** warning: "
			     "file %s becomes empty but is not deleted"),
			   patch->new_name);
/*
 * Read a binary hunk and return a new fragment; fragment->patch
 * points at an allocated memory that the caller must free, so
 * it is marked as "->free_patch = 1".
 */
	if (starts_with(buffer, "delta ")) {
	else if (starts_with(buffer, "literal ")) {
	frag->free_patch = 1;
	error(_("corrupt binary patch at line %d: %.*s"),
		return error(_("unrecognized binary patch at line %d"), linenr-1);
/*
 * Read the patch text in "buffer" that extends for "size" bytes; stop
 * reading after seeing a single patch (i.e. changes to a single file).
 * Create fragments (i.e. patch hunks) and hang them to the given patch.
 * Return the number of bytes consumed, so that the caller can call us
 * again for the next patch.
 */
			static const char *binhdr[] = {
				"Binary files ",
				"Files ",
				NULL,
			};
			int i;
			die(_("patch with only garbage at line %d"), linenr);
			return error(_("unable to read symlink %s"), path);
			return error(_("unable to open or read %s"), path);
	int i, ctx, reduced;
	assert(postlen
	       ? fixed_preimage.nr == preimage->nr
	       : fixed_preimage.nr <= preimage->nr);
	for (i = 0; i < fixed_preimage.nr; i++)
	 * done in-place when we are shrinking it with whitespace
	 * fixing, but needs a new buffer when ignoring whitespace or
	 * expanding leading tabs to spaces.
	 *

	for (i = reduced = ctx = 0; i < postimage->nr; i++) {

		/*
		 * preimage is expected to run out, if the caller
		 * fixed addition of trailing blank lines.
		 */
		if (preimage->nr <= ctx) {
			reduced++;
			continue;
		}
	postimage->nr -= reduced;
	size_t fixed_len, postlen;
	postlen = 0;
		postlen += tgtfix.len;
	if (postlen < postimage->len)
		postlen = 0;
			       fixed_buf, fixed_len, postlen);
/*
 * The change from "preimage" and "postimage" has been found to
 * apply at applied_pos (counts in line numbers) in "img".
 * Update "img" to remove "preimage" and replace it with "postimage".
 */
/*
 * Use the patch-hunk text in "frag" to prepare two images (preimage and
 * postimage) for the hunk.  Find lines that match "preimage" in "img" and
 * replace the part of "img" with "postimage" text.
 */
				error(_("invalid start of line: '%c'"), first);
			fprintf_ln(stderr,
				   Q_("Hunk #%d succeeded at %d (offset %d line).",
				      "Hunk #%d succeeded at %d (offset %d lines).",
				      offset),
				   nth_fragment, applied_pos + 1, offset);
			fprintf_ln(stderr, _("Context reduced to (%ld/%ld)"
					     " to apply fragment at %d"),
				   leading, trailing, applied_pos+1);
			error(_("while searching for:\n%.*s"),
		return error(_("missing binary patch data for '%s'"),
		img->buf = xmemdupz(fragment->patch, img->len);
/*
 * Replace "img" with the result of applying the binary patch.
 * The binary patch data itself in patch->fragment is still kept
 * but the preimage prepared by the caller in "img" is freed here
 * or in the helper function apply_binary_fragment() this calls.
 */
			return error(_("binary patch does not apply to '%s'"),
			return error(_("binary patch to '%s' creates incorrect result (expecting %s, got %s)"),
			error(_("patch failed: %s:%ld"), name, frag->oldpos);
static int read_blob_object(struct strbuf *buf, const unsigned char *sha1, unsigned mode)
	if (S_ISGITLINK(mode)) {
		strbuf_addf(buf, "Subproject commit %s\n", sha1_to_hex(sha1));
		result = read_sha1_file(sha1, &type, &sz);
static int read_file_or_gitlink(const struct cache_entry *ce, struct strbuf *buf)
{
	if (!ce)
		return 0;
	return read_blob_object(buf, ce->sha1, ce->ce_mode);
}

 * path that a previously applied patch has already removed, or
 * PATH_TO_BE_DELETED for a path that a later patch would remove.
 *
 * The latter is needed to deal with a case where two paths A and B
 * are swapped by first renaming A to B and then renaming B to A;
 * moving A to B should not be prevented due to presence of B as we
 * will remove it in a later patch.
#define PATH_TO_BE_DELETED ((struct patch *) -2)
static int checkout_target(struct index_state *istate,
			   struct cache_entry *ce, struct stat *st)
{
	struct checkout costate;

	memset(&costate, 0, sizeof(costate));
	costate.base_dir = "";
	costate.refresh_cache = 1;
	costate.istate = istate;
	if (checkout_entry(ce, &costate, NULL) || lstat(ce->name, st))
		return error(_("cannot checkout %s"), ce->name);
	return 0;
}

static struct patch *previous_patch(struct patch *patch, int *gone)
{
	struct patch *previous;

	*gone = 0;
	if (patch->is_copy || patch->is_rename)
		return NULL; /* "git" patches do not depend on the order */

	previous = in_fn_table(patch->old_name);
	if (!previous)
		return NULL;

	if (to_be_deleted(previous))
		return NULL; /* the deletion hasn't happened yet */

	if (was_deleted(previous))
		*gone = 1;

	return previous;
}

static int verify_index_match(const struct cache_entry *ce, struct stat *st)
{
	if (S_ISGITLINK(ce->ce_mode)) {
		if (!S_ISDIR(st->st_mode))
			return -1;
		return 0;
	}
	return ce_match_stat(ce, st, CE_MATCH_IGNORE_VALID|CE_MATCH_IGNORE_SKIP_WORKTREE);
}

#define SUBMODULE_PATCH_WITHOUT_INDEX 1

static int load_patch_target(struct strbuf *buf,
			     const struct cache_entry *ce,
			     struct stat *st,
			     const char *name,
			     unsigned expected_mode)
{
	if (cached) {
		if (read_file_or_gitlink(ce, buf))
			return error(_("read of %s failed"), name);
	} else if (name) {
		if (S_ISGITLINK(expected_mode)) {
			if (ce)
				return read_file_or_gitlink(ce, buf);
			else
				return SUBMODULE_PATCH_WITHOUT_INDEX;
		} else {
			if (read_old_data(st, name, buf))
				return error(_("read of %s failed"), name);
		}
	}
	return 0;
}

/*
 * We are about to apply "patch"; populate the "image" with the
 * current version we have, from the working tree or from the index,
 * depending on the situation e.g. --cached/--index.  If we are
 * applying a non-git patch that incrementally updates the tree,
 * we read from the result of a previous diff.
 */
static int load_preimage(struct image *image,
			 struct patch *patch, struct stat *st,
			 const struct cache_entry *ce)
	struct patch *previous;
	int status;
	previous = previous_patch(patch, &status);
	if (status)
		return error(_("path %s has been renamed/deleted"),
			     patch->old_name);
	if (previous) {
		/* We have a patched copy in memory; use that. */
		strbuf_add(&buf, previous->result, previous->resultsize);
	} else {
		status = load_patch_target(&buf, ce, st,
					   patch->old_name, patch->old_mode);
		if (status < 0)
			return status;
		else if (status == SUBMODULE_PATCH_WITHOUT_INDEX) {
			/*
			 * There is no way to apply subproject
			 * patch without looking at the index.
			 * NEEDSWORK: shouldn't this be flagged
			 * as an error???
			 */
			free_fragment_list(patch->fragments);
			patch->fragments = NULL;
		} else if (status) {
			return error(_("read of %s failed"), patch->old_name);
	prepare_image(image, img, len, !patch->is_binary);
	return 0;
}
static int three_way_merge(struct image *image,
			   char *path,
			   const unsigned char *base,
			   const unsigned char *ours,
			   const unsigned char *theirs)
{
	mmfile_t base_file, our_file, their_file;
	mmbuffer_t result = { NULL };
	int status;
	read_mmblob(&base_file, base);
	read_mmblob(&our_file, ours);
	read_mmblob(&their_file, theirs);
	status = ll_merge(&result, path,
			  &base_file, "base",
			  &our_file, "ours",
			  &their_file, "theirs", NULL);
	free(base_file.ptr);
	free(our_file.ptr);
	free(their_file.ptr);
	if (status < 0 || !result.ptr) {
		free(result.ptr);
		return -1;
	}
	clear_image(image);
	image->buf = result.ptr;
	image->len = result.size;

	return status;
}
/*
 * When directly falling back to add/add three-way merge, we read from
 * the current contents of the new_name.  In no cases other than that
 * this function will be called.
 */
static int load_current(struct image *image, struct patch *patch)
{
	struct strbuf buf = STRBUF_INIT;
	int status, pos;
	size_t len;
	char *img;
	struct stat st;
	struct cache_entry *ce;
	char *name = patch->new_name;
	unsigned mode = patch->new_mode;

	if (!patch->is_new)
		die("BUG: patch to %s is not a creation", patch->old_name);

	pos = cache_name_pos(name, strlen(name));
	if (pos < 0)
		return error(_("%s: does not exist in index"), name);
	ce = active_cache[pos];
	if (lstat(name, &st)) {
		if (errno != ENOENT)
			return error(_("%s: %s"), name, strerror(errno));
		if (checkout_target(&the_index, ce, &st))
			return -1;
	}
	if (verify_index_match(ce, &st))
		return error(_("%s: does not match index"), name);

	status = load_patch_target(&buf, ce, &st, name, mode);
	if (status < 0)
		return status;
	else if (status)
		return -1;
	img = strbuf_detach(&buf, &len);
	prepare_image(image, img, len, !patch->is_binary);
static int try_threeway(struct image *image, struct patch *patch,
			struct stat *st, const struct cache_entry *ce)
	unsigned char pre_sha1[20], post_sha1[20], our_sha1[20];
	struct strbuf buf = STRBUF_INIT;
	size_t len;
	int status;
	char *img;
	struct image tmp_image;

	/* No point falling back to 3-way merge in these cases */
	if (patch->is_delete ||
	    S_ISGITLINK(patch->old_mode) || S_ISGITLINK(patch->new_mode))
		return -1;

	/* Preimage the patch was prepared for */
	if (patch->is_new)
		write_sha1_file("", 0, blob_type, pre_sha1);
	else if (get_sha1(patch->old_sha1_prefix, pre_sha1) ||
		 read_blob_object(&buf, pre_sha1, patch->old_mode))
		return error("repository lacks the necessary blob to fall back on 3-way merge.");

	fprintf(stderr, "Falling back to three-way merge...\n");
	img = strbuf_detach(&buf, &len);
	prepare_image(&tmp_image, img, len, 1);
	/* Apply the patch to get the post image */
	if (apply_fragments(&tmp_image, patch) < 0) {
		clear_image(&tmp_image);
		return -1;
	}
	/* post_sha1[] is theirs */
	write_sha1_file(tmp_image.buf, tmp_image.len, blob_type, post_sha1);
	clear_image(&tmp_image);

	/* our_sha1[] is ours */
	if (patch->is_new) {
		if (load_current(&tmp_image, patch))
			return error("cannot read the current contents of '%s'",
				     patch->new_name);
	} else {
		if (load_preimage(&tmp_image, patch, st, ce))
			return error("cannot read the current contents of '%s'",
				     patch->old_name);
	}
	write_sha1_file(tmp_image.buf, tmp_image.len, blob_type, our_sha1);
	clear_image(&tmp_image);

	/* in-core three-way merge between post and our using pre as base */
	status = three_way_merge(image, patch->new_name,
				 pre_sha1, our_sha1, post_sha1);
	if (status < 0) {
		fprintf(stderr, "Failed to fall back on three-way merge...\n");
		return status;
	}

	if (status) {
		patch->conflicted_threeway = 1;
		if (patch->is_new)
			hashclr(patch->threeway_stage[0]);
		else
			hashcpy(patch->threeway_stage[0], pre_sha1);
		hashcpy(patch->threeway_stage[1], our_sha1);
		hashcpy(patch->threeway_stage[2], post_sha1);
		fprintf(stderr, "Applied patch to '%s' with conflicts.\n", patch->new_name);
	} else {
		fprintf(stderr, "Applied patch to '%s' cleanly.\n", patch->new_name);
static int apply_data(struct patch *patch, struct stat *st, const struct cache_entry *ce)
	struct image image;

	if (load_preimage(&image, patch, st, ce) < 0)
		return -1;

	if (patch->direct_to_threeway ||
	    apply_fragments(&image, patch) < 0) {
		/* Note: with --reject, apply_fragments() returns 0 */
		if (!threeway || try_threeway(&image, patch, st, ce) < 0)
	patch->result = image.buf;
	patch->resultsize = image.len;
	add_to_fn_table(patch);
	free(image.line_allocated);

	if (0 < patch->is_delete && patch->resultsize)
		return error(_("removal patch leaves file contents"));

	return 0;
/*
 * If "patch" that we are looking at modifies or deletes what we have,
 * we would want it not to lose any local modification we have, either
 * in the working tree or in the index.
 *
 * This also decides if a non-git patch is a creation patch or a
 * modification to an existing empty file.  We do not check the state
 * of the current tree for a creation patch in this function; the caller
 * check_patch() separately makes sure (and errors out otherwise) that
 * the path the patch creates does not exist in the current tree.
 */
	struct patch *previous = NULL;
	int stat_ret = 0, status;
	previous = previous_patch(patch, &status);
	if (status)
		return error(_("path %s has been renamed/deleted"), old_name);
	if (previous) {
		st_mode = previous->new_mode;
			return error(_("%s: %s"), old_name, strerror(errno));
	if (check_index && !previous) {
			return error(_("%s: does not exist in index"), old_name);
			if (checkout_target(&the_index, *ce, st))
			return error(_("%s: does not match index"), old_name);
		return error(_("%s: %s"), old_name, strerror(errno));
	if (!cached && !previous)
		return error(_("%s: wrong type"), old_name);
		warning(_("%s has type %o, expected %o"),
	free(patch->old_name);

#define EXISTS_IN_INDEX 1
#define EXISTS_IN_WORKTREE 2

static int check_to_create(const char *new_name, int ok_if_exists)
{
	struct stat nst;

	if (check_index &&
	    cache_name_pos(new_name, strlen(new_name)) >= 0 &&
	    !ok_if_exists)
		return EXISTS_IN_INDEX;
	if (cached)
		return 0;

	if (!lstat(new_name, &nst)) {
		if (S_ISDIR(nst.st_mode) || ok_if_exists)
			return 0;
		/*
		 * A leading component of new_name might be a symlink
		 * that is going to be removed with this patch, but
		 * still pointing at somewhere that has the path.
		 * In such a case, path "new_name" does not exist as
		 * far as git is concerned.
		 */
		if (has_symlink_leading_path(new_name, strlen(new_name)))
			return 0;

		return EXISTS_IN_WORKTREE;
	} else if ((errno != ENOENT) && (errno != ENOTDIR)) {
		return error("%s: %s", new_name, strerror(errno));
	}
	return 0;
}

/*
 * Check and apply the patch in-core; leave the result in patch->result
 * for the caller to write it out to the final destination.
 */
	/*
	 * A type-change diff is always split into a patch to delete
	 * old, immediately followed by a patch to create new (see
	 * diff.c::run_diff()); in such a case it is Ok that the entry
	 * to be deleted by the previous patch is still in the working
	 * tree and in the index.
	 *
	 * A patch to swap-rename between A and B would first rename A
	 * to B and then rename B to A.  While applying the first one,
	 * the presence of B should not stop A from getting renamed to
	 * B; ask to_be_deleted() about the later rename.  Removal of
	 * B and rename from A to B is handled the same way by asking
	 * was_deleted().
	 */
	    (was_deleted(tpatch) || to_be_deleted(tpatch)))
	    ((0 < patch->is_new) || patch->is_rename || patch->is_copy)) {
		int err = check_to_create(new_name, ok_if_exists);

		if (err && threeway) {
			patch->direct_to_threeway = 1;
		} else switch (err) {
		case 0:
			break; /* happy */
		case EXISTS_IN_INDEX:
			return error(_("%s: already exists in index"), new_name);
			break;
		case EXISTS_IN_WORKTREE:
			return error(_("%s: already exists in working directory"),
				     new_name);
		default:
			return err;

		if ((patch->old_mode ^ patch->new_mode) & S_IFMT) {
			if (same)
				return error(_("new mode (%o) of %s does not "
					       "match old mode (%o)"),
					patch->new_mode, new_name,
					patch->old_mode);
			else
				return error(_("new mode (%o) of %s does not "
					       "match old mode (%o) of %s"),
					patch->new_mode, new_name,
					patch->old_mode, old_name);
		}
		return error(_("%s: patch does not apply"), name);
				       _("Checking patch %s..."), patch);
static int preimage_sha1_in_gitlink_patch(struct patch *p, unsigned char sha1[20])
{
	/*
	 * A usable gitlink patch has only one fragment (hunk) that looks like:
	 * @@ -1 +1 @@
	 * -Subproject commit <old sha1>
	 * +Subproject commit <new sha1>
	 * or
	 * @@ -1 +0,0 @@
	 * -Subproject commit <old sha1>
	 * for a removal patch.
	 */
	struct fragment *hunk = p->fragments;
	static const char heading[] = "-Subproject commit ";
	char *preimage;

	if (/* does the patch have only one hunk? */
	    hunk && !hunk->next &&
	    /* is its preimage one line? */
	    hunk->oldpos == 1 && hunk->oldlines == 1 &&
	    /* does preimage begin with the heading? */
	    (preimage = memchr(hunk->patch, '\n', hunk->size)) != NULL &&
	    starts_with(++preimage, heading) &&
	    /* does it record full SHA-1? */
	    !get_sha1_hex(preimage + sizeof(heading) - 1, sha1) &&
	    preimage[sizeof(heading) + 40 - 1] == '\n' &&
	    /* does the abbreviated name on the index line agree with it? */
	    starts_with(preimage + sizeof(heading) - 1, p->old_sha1_prefix))
		return 0; /* it all looks fine */

	/* we may have full object name on the index line */
	return get_sha1_hex(p->old_sha1_prefix, sha1);
}

	static struct lock_file lock;
		if (S_ISGITLINK(patch->old_mode)) {
			if (!preimage_sha1_in_gitlink_patch(patch, sha1))
				; /* ok, the textual part looks sane */
			else
				die("sha1 information is lacking or useless for submoule %s",
				    name);
		} else if (!get_sha1_blob(patch->old_sha1_prefix, sha1)) {
			; /* ok */
		} else if (!patch->lines_added && !patch->lines_deleted) {
			/* mode-only change: update the current */
			if (get_current_sha1(patch->old_name, sha1))
				die("mode change for %s, which is not "
				    "in current HEAD", name);
		} else
			die("sha1 information is lacking or useless "
			    "(%s).", name);

		ce = make_cache_entry(patch->old_mode, sha1, name, 0, 0);
			die(_("make_cache_entry failed for path '%s'"), name);
	hold_lock_file_for_update(&lock, filename, LOCK_DIE_ON_ERROR);
	if (write_locked_index(&result, &lock, COMMIT_LOCK))
			die(_("unable to remove %s from index"), patch->old_name);
	ce->ce_flags = create_ce_flags(0);
	ce->ce_namelen = namelen;
		const char *s;
		if (!skip_prefix(buf, "Subproject commit ", &s) ||
		    get_sha1_hex(s, ce->sha1))
			die(_("corrupt patch for submodule %s"), path);
				die_errno(_("unable to stat newly created file '%s'"),
			die(_("unable to create backing store for newly created file %s"), path);
		die(_("unable to add cache entry for %s"), path);
		die_errno(_("closing file '%s'"), path);
	die_errno(_("unable to write file '%s' mode %o"), path, mode);
}

static void add_conflicted_stages_file(struct patch *patch)
{
	int stage, namelen;
	unsigned ce_size, mode;
	struct cache_entry *ce;

	if (!update_index)
		return;
	namelen = strlen(patch->new_name);
	ce_size = cache_entry_size(namelen);
	mode = patch->new_mode ? patch->new_mode : (S_IFREG | 0644);

	remove_file_from_cache(patch->new_name);
	for (stage = 1; stage < 4; stage++) {
		if (is_null_sha1(patch->threeway_stage[stage - 1]))
			continue;
		ce = xcalloc(1, ce_size);
		memcpy(ce->name, patch->new_name, namelen);
		ce->ce_mode = create_ce_mode(mode);
		ce->ce_flags = create_ce_flags(stage);
		ce->ce_namelen = namelen;
		hashcpy(ce->sha1, patch->threeway_stage[stage - 1]);
		if (add_cache_entry(ce, ADD_CACHE_OK_TO_ADD) < 0)
			die(_("unable to add cache entry for %s"), patch->new_name);
	}

	if (patch->conflicted_threeway)
		add_conflicted_stages_file(patch);
	else
		add_index_file(path, mode, buf, size);
	struct strbuf sb = STRBUF_INIT;
				       _("Applied patch %s cleanly."), patch);
		die(_("internal error"));
	strbuf_addf(&sb, Q_("Applying patch %%s with %d reject...",
			    "Applying patch %%s with %d rejects...",
			    cnt),
		    cnt);
	say_patch_name(stderr, sb.buf, patch);
	strbuf_release(&sb);
		warning(_("truncating .rej filename to %.*s.rej"),
		return error(_("cannot open %s: %s"), namebuf, strerror(errno));
	 * this is a git patch by saying --git or giving extended
			fprintf_ln(stderr, _("Hunk #%d applied cleanly."), cnt);
		fprintf_ln(stderr, _("Rejected hunk #%d."), cnt);
	struct string_list cpath = STRING_LIST_INIT_DUP;
				if (phase == 1) {
					if (write_out_one_reject(l))
						errs = 1;
					if (l->conflicted_threeway) {
						string_list_append(&cpath, l->new_name);
						errs = 1;
					}
				}

	if (cpath.nr) {
		struct string_list_item *item;

		sort_string_list(&cpath);
		for_each_string_list_item(item, &cpath)
			fprintf(stderr, "U %s\n", item->string);
		string_list_clear(&cpath, 0);

		rerere(0);
	}

		if (!wildmatch(it->string, pathname, 0, NULL))
		prefix_one(&p->new_name);
		prefix_one(&p->old_name);
	struct strbuf buf = STRBUF_INIT; /* owns the patch text */
			free_patch(patch);
		die(_("unrecognized input"));
			die(_("unable to read index file"));
	if (apply && write_out_results(list)) {
		if (apply_with_reject)
			exit(1);
		/* with --3way, we still need to write the index out */
		return 1;
	}
	free_patch_list(list);
	string_list_clear(&fn_table, 0);
		{ OPTION_CALLBACK, 0, "exclude", NULL, N_("path"),
			N_("don't apply changes matching the given path"),
		{ OPTION_CALLBACK, 0, "include", NULL, N_("path"),
			N_("apply changes matching the given path"),
		{ OPTION_CALLBACK, 'p', NULL, NULL, N_("num"),
			N_("remove <num> leading slashes from traditional diff paths"),
		OPT_BOOL(0, "no-add", &no_add,
			N_("ignore additions made by the patch")),
		OPT_BOOL(0, "stat", &diffstat,
			N_("instead of applying the patch, output diffstat for the input")),
		OPT_BOOL(0, "numstat", &numstat,
			N_("show number of added and deleted lines in decimal notation")),
		OPT_BOOL(0, "summary", &summary,
			N_("instead of applying the patch, output a summary for the input")),
		OPT_BOOL(0, "check", &check,
			N_("instead of applying the patch, see if the patch is applicable")),
		OPT_BOOL(0, "index", &check_index,
			N_("make sure the patch is applicable to the current index")),
		OPT_BOOL(0, "cached", &cached,
			N_("apply a patch without touching the working tree")),
		OPT_BOOL(0, "apply", &force_apply,
			N_("also apply the patch (use with --stat/--summary/--check)")),
		OPT_BOOL('3', "3way", &threeway,
			 N_( "attempt three-way merge if a patch does not apply")),
			N_("build a temporary index based on embedded index information")),
			N_("paths are separated with NUL character"),
				N_("ensure at least <n> lines of context match")),
		{ OPTION_CALLBACK, 0, "whitespace", &whitespace_option, N_("action"),
			N_("detect new or modified lines that have whitespace errors"),
			N_("ignore changes in whitespace when finding context"),
			N_("ignore changes in whitespace when finding context"),
		OPT_BOOL('R', "reverse", &apply_in_reverse,
			N_("apply the patch in reverse")),
		OPT_BOOL(0, "unidiff-zero", &unidiff_zero,
			N_("don't expect at least one line of context")),
		OPT_BOOL(0, "reject", &apply_with_reject,
			N_("leave the rejected hunks in corresponding *.rej files")),
		OPT_BOOL(0, "allow-overlap", &allow_overlap,
			N_("allow overlapping hunks")),
		OPT__VERBOSE(&apply_verbosely, N_("be verbose")),
			N_("tolerate incorrectly detected missing new-line at the end of file"),
			N_("do not trust the line counts in the hunk headers"),
		{ OPTION_CALLBACK, 0, "directory", NULL, N_("root"),
			N_("prepend <root> to all filenames"),
	if (apply_with_reject && threeway)
		die("--reject and --3way cannot be used together.");
	if (cached && threeway)
		die("--cached and --3way cannot be used together.");
	if (threeway) {
		if (is_not_gitdir)
			die(_("--3way outside a repository"));
		check_index = 1;
	}
		die(_("--index outside a repository"));
			die(_("--cached outside a repository"));
			die_errno(_("can't open patch '%s'"), arg);
			warning(Q_("squelched %d whitespace error",
				   "squelched %d whitespace errors",
				   squelched),
				squelched);
			die(Q_("%d line adds whitespace errors.",
			       "%d lines add whitespace errors.",
			       whitespace_error),
			    whitespace_error);
			warning(Q_("%d line adds whitespace errors.",
				   "%d lines add whitespace errors.",
				   whitespace_error),
				whitespace_error);
		if (write_locked_index(&the_index, &lock_file, COMMIT_LOCK))
			die(_("Unable to write new index file"));