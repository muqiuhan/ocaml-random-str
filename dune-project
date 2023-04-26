(lang dune 3.7)

(name random_str)

(generate_opam_files true)

(source
 (github muqiuhan/ocaml-random-str))

(authors "Muqiu Han")

(maintainers "Muqiu Han")

(license MIT)

(documentation https://github.com/muqiuhan/ocaml-random-str)

(package
 (allow_empty)
 (name random_str)
 (synopsis "A high-performance random string generation algorithm based on Xorshift")
 (description "A high-performance random string generation algorithm based on Xorshift")
 (depends ocaml dune)
 (tags
  (xorshift "random str" random)))

; See the complete stanza docs at https://dune.readthedocs.io/en/stable/dune-files.html#dune-project
