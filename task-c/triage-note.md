# Task C triage note (local Semgrep run)

I ran a local Semgrep scan on `webapplication/app.py` using the OWASP Top 10 ruleset and got 46 findings.

High-frequency result themes:

- SQL injection patterns tied to dynamic SQL composition and `execute()` usage
- tainted SQL string handling in Flask routes
- raw HTML concatenation/formatting patterns (XSS style risk)
- debug mode enabled warning

Triage decision approach used:

1. Prioritise findings where user input reaches SQL execution first.
2. Then review stored/reflected output handling paths for XSS risk.
3. Treat debug-mode warnings as environment/config hardening items.
4. Mark exact false positives only after reading route context and data flow.

This note is intentionally short and is meant to accompany the JSON report and CI screenshots.
