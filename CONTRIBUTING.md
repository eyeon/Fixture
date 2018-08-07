# Contributing

When contributing to this repository, please first discuss the change you wish to make via issue,
email, Telegram or any other method with the owners of this repository before making a change. 

Please check the [ROADMAP file](https://github.com/eyeon/Fixture/blob/master/README.MD) before raising an issue. There's a chance that the missing feature you
are expecting is already in our TODO list. We will get there soon.

Please note we have a [code of conduct](https://github.com/eyeon/Fixture/blob/master/CODE_OF_CONDUCT.md), please follow it in all your interactions with the project.

Join the telegram channel at: https://t.me/eyeon_social if you have any queries, suggestions etc.

## General rules

 -  Commits must be atomic. They should reflect a set of distinct changes as a single operation that solve one problem at a time.
 -  Commit messages must be meaningful, clear and concise. Stress on your grammar, it's fine to google the correct way to say something, English isn't everyone's first language.
 - Commits should do exactly what their message says. If a commit affects quite a few files, and does a few related things, mention them in the commit description. Refrain from using `git commit -m` in such cases.
 -  IDE configuration files/temp files are not meant to be a part of the repository and they should remain so.
 -  Variable names like `a`, `x`, `foo` are unacceptable, use variable names that describes its purpose.
 -  Format the file with `uncrustify` using the `uncrustify.cfg` provided with the project before submitting any patch.
   
## Pull Request Process

 -  Check if there's already a PR assigned to someone that solves a similar problem to yours.
 - Ensure that the pull request is being sent from a hotfix/feature branch and not from `master`.
 - Check the issue page if the feature you are trying to add/bug you are trying to fix is already in the list. If it does, mention the issue number in parentheses with the pull request.
 - Provide a clear, concise description of why this pull request is necessary and what value it adds. Make sure that your PR doesn't contain any more or less than what the PR description says.
 - One PR should do only one thing only. No more, no less. If you want to implement two new features, open two PRs.
