# 7021SCN Software Security Portfolio
**Student name:** Nihaal Jitendrakumar Umrekar
**Student ID:** 16320763  

This repository contains my full practical portfolio for 7021SCN Software Security.  
The work is organised into five assessed tasks (A-E), with one shared target Flask application used for modelling and testing tasks.

---

## Repository Structure

- `task-a/` - Vulnerability discovery and remediation in C.
- `task-b/` - Threat modelling and SDLC analysis for the Flask web application.
- `task-c/` - Automated SAST using Semgrep in GitHub Actions.
- `task-d/` - Dynamic analysis using OWASP ZAP.
- `task-e/` - Supply chain and compliance work (Docker + SBOM).
- `webapplication/` - Target Flask application used in Tasks B, C, D, and E.
- `.github/workflows/` - CI workflow for Semgrep SAST pipeline.

---

### Task A - Vulnerability Discovery and Remediation

**Objective:** identify and remediate a memory safety issue in a small C program.

**Implemented outputs:**
- vulnerable implementation: `task-a/vulnerable.c`
- remediated implementation: `task-a/secure.c`
- reproducible build config: `task-a/Makefile`
- supporting evidence: `task-a/evidence/`

**Security focus:**
- demonstrates stack corruption risk from unbounded copy (`strcpy`)
- demonstrates safer boundary-aware handling with fail-safe behaviour in secure version

### Task B - Threat Modelling and SDLC

**Objective:** model the Flask app architecture and map key threats to controls.

**Implemented outputs:**
- full analysis report: `task-b/README.md`
- DFD diagram set:
  - `task-b/diagrams/level-1-dfd-my-shop-trust-boundaries.png`
  - `task-b/diagrams/level-2-dfd-auth-and-product-flow.png`
  - `task-b/diagrams/level-3-dfd-admin-and-review-control-flow.png`

**Security focus:**
- trust boundaries and risky data flows
- STRIDE analysis connected to observed route/query behaviour
- practical SDLC-aligned mitigation requirements

### Task C - Automated Security Testing

**Objective:** integrate static security checks into CI/CD.

**Implemented outputs:**
- workflow pipeline: `.github/workflows/semgrep-sast.yml`
- task write-up: `task-c/README.md`
- evidence screenshots: `task-c/evidence/`
- Semgrep outputs:
  - `task-c/semgrep-report.json`
  - `task-c/semgrep-report-local.json`
- triage note: `task-c/triage-note.md`

**Security focus:**
- shift-left scanning on push to `main`
- machine-readable findings as artifacts
- reflection on SAST limits (context blindness and triage need)

### Task D - Dynamic Analysis and Exploit Validation

**Objective:** validate exploitability of runtime behaviour using DAST.

**Implemented outputs:**
- analysis/report: `task-d/README.md`
- evidence chain: `task-d/evidence/` (setup, scan, alerts, request/response, impact)

**Security focus:**
- confirms runtime risk paths beyond static patterns
- documents practical DAST limitations and analyst guidance requirement

### Task E - Compliance and Supply Chain

**Objective:** improve software composition visibility and compliance readiness.

**Implemented outputs:**
- container setup:
  - `webapplication/Dockerfile`
  - `webapplication/.dockerignore`
- SBOM artifacts:
  - `task-e/sbom-webapplication-cyclonedx.json`
  - `task-e/sbom-webapplication-locked-cyclonedx.json`
  - `task-e/sbom-webapplication-image-cyclonedx.json`
  - `task-e/requirements-locked.txt`
- task write-up and evidence mapping: `task-e/README.md`

**Security focus:**
- dependency and image-level visibility
- machine-readable SBOM evidence to support SSDF-style supply chain assurance

---

