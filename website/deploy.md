### Deploying the website

Building the website requires Hugo: https://gohugo.io/getting-started/installing/

Clone the repository:

    git clone git@github.com:uchicago-cs/cmsc22000.git

Make sure to initialize the submodules:

    git submodule update --init

Then, run the following inside `website/`:

echo "public" >> .gitignore
git worktree add -B gh-pages public origin/gh-pages

After making a change to the website, simply run this:

    ./commit-gh-pages-files.sh

Push the changes to GitHub Pages:

    git push --all
