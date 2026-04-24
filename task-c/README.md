# Task C - Automated security testing

For this task I set up Semgrep in GitHub Actions so static security scanning runs automatically when code is pushed to `main`.

The point is to make security checks part of normal development, not something done manually at the end.

## Workflow used

File:

- `.github/workflows/semgrep-sast.yml`

What it does:

1. Checks out the repository with `actions/checkout@v4`
2. Installs Semgrep with pip
3. Runs this scan command:

`semgrep scan --config="p/owasp-top-ten" --json -o semgrep-report.json`

4. Uploads the JSON report as `semgrep-audit-report`

Important detail: upload uses `if: always()` so the report is still saved even if scan step fails.

## Why this setup matters

Running SAST on every push helps avoid the common issue of forgetting to run checks.

It also gives a consistent pipeline result for every code update and keeps evidence in one place (Actions logs + artifact).

## What Semgrep is expected to flag in this project

Target file for this task:

- `webapplication/app.py`

Likely findings include:

- SQL injection-style patterns from f-string queries passed to `execute()`
- hardcoded `app.secret_key`
- possible warnings around dynamic HTML output and debug configuration

## Critical reflection: limits of SAST

Semgrep is useful, but it is still context-blind.

It can identify risky coding patterns quickly, but it cannot fully understand business logic, deployment controls, or whether every finding is truly exploitable in the exact runtime environment.

That is why raw scanner output always needs manual triage.

### How I would triage findings

1. Confirm user input reaches the risky sink
2. Check realistic exploitability in this app
3. Evaluate impact if exploited
4. Decide fix / accept / suppress and record reason

Without this step, teams either ignore important issues or lose time on low-priority noise.

## Evidence to include for marking

After pushing Task C and triggering the workflow, capture and keep:

- screenshot of `.github/workflows/semgrep-sast.yml`
- screenshot of Actions run summary
- screenshot of Semgrep step log
- screenshot showing artifact `semgrep-audit-report`
- downloaded `semgrep-report.json`
- short triage note based on real findings

Suggested location:

- `task-c/evidence/`

## References

- Semgrep docs: https://semgrep.dev/docs/
- OWASP Top 10: https://owasp.org/www-project-top-ten/

(References will be formatted to final module style before submission.)
