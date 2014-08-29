. "$TEST_DIRECTORY/lib-gpg.sh"
test_expect_success 'format %w(11,1,2)' '
	git log -2 --format="%w(11,1,2)This is the %s commit." > actual &&
test_expect_success 'git log --no-walk=sorted <commits> sorts by commit time' '
	git log --no-walk=sorted --oneline 5d31159 804a787 394ef78 > actual &&
	test_cmp expect actual
'

test_expect_success 'git log --no-walk=unsorted <commits> leaves list of commits as given' '
	git log --no-walk=unsorted --oneline 5d31159 804a787 394ef78 > actual &&
	test_cmp expect actual
'

test_expect_success 'log -F -E --grep=<ere> uses ere' '
	echo second >expect &&
	git log -1 --pretty="tformat:%s" -F -E --grep=s.c.nd >actual &&
	test_cmp expect actual
'

test_expect_success 'log --raw --graph -m with merge' '
	git log --raw --graph --oneline -m master | head -n 500 >actual &&
	grep "initial" actual
'

test_expect_success 'diff-tree --graph' '
	git diff-tree --graph master^ | head -n 500 >actual &&
	grep "one" actual
'

	test_config log.decorate true &&
	test_config log.decorate no &&
	test_config log.decorate 1 &&
	test_config log.decorate short &&
	test_config log.decorate full &&
	test_unconfig log.decorate &&
	test_config log.decorate full &&
	test_config log.abbrevCommit true &&
test_expect_success 'git log -c --follow' '
	test_create_repo follow-c &&
	(
		cd follow-c &&
		test_commit initial file original &&
		git rm file &&
		test_commit rename file2 original &&
		git reset --hard initial &&
		test_commit modify file foo &&
		git merge -m merge rename &&
		git log -c --follow file2
	)
'

| |  reach.t | 1 +
| | |    octopus-b.t | 1 +
| |    octopus-a.t | 1 +
|    seventh.t | 1 +
| | | |  tangle-a | 1 +
| | | |    2 | 1 +
| | | |  1 | 1 +
| | | |  one | 1 +
| | |    a/two | 1 -
| | |  a/two | 1 +
| |    ein | 1 +
|    ichi | 1 +
|    one  | 1 -
|  one | 2 +-
   one | 1 +