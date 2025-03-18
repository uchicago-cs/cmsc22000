# Configuration file for the Sphinx documentation builder.
#
# For the full list of built-in configuration values, see the documentation:
# https://www.sphinx-doc.org/en/master/usage/configuration.html

# -- Project information -----------------------------------------------------
# https://www.sphinx-doc.org/en/master/usage/configuration.html#project-information

project = 'CMSC 22000 - Introduction to Software Development'
copyright = '2025, University of Chicago'
author = 'University of Chicago'
release = '2025-spring'

# -- General configuration ---------------------------------------------------
# https://www.sphinx-doc.org/en/master/usage/configuration.html#general-configuration

extensions = []

templates_path = ['_templates']
exclude_patterns = ['_build', 'Thumbs.db', '.DS_Store', 'venv']



# -- Options for HTML output -------------------------------------------------
# https://www.sphinx-doc.org/en/master/usage/configuration.html#options-for-html-output

html_theme = "pydata_sphinx_theme"
html_static_path = ['_static']
html_css_files = [
    'css/chiweb.css',
]
html_theme_options = {
    "logo": {
        "text": "CMSC 22000",
    },
    "show_prev_next": False,
    "secondary_sidebar_items": ["page-toc"],
}

html_sidebars = {
  "**": []
}