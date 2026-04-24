# 7021SCN portfolio

This repository is my Software Security portfolio for 7021SCN.

## What is in here

- `task-a/` - Vulnerability discovery and remediation in C (buffer overflow + secure fix)
- `task-b/` - Threat modelling and SDLC write-up for the Flask shop app
- `task-c/` - Automated SAST using Semgrep in GitHub Actions
- `task-d/` - Dynamic testing (ZAP/Burp) notes and evidence
- `task-e/` - SBOM and compliance notes
- `webapplication/` - Local Flask app used as the target system for Tasks B/D/C analysis
- `report/` - Place the final 500-word Turnitin Word document here

## Submission reminders

- Keep this repo public before final hand-in so markers can open it.
- Put the repo link at the end of the Turnitin report.
- If the brief asks for a `.docx` in the repo root, add a copy there too.

## Quick run (Task A)

```bash
cd task-a
make vulnerable
make secure
```
