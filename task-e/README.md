# Task E - Compliance and software supply chain (SBOM)

For Task E, I generated SBOM evidence for the Flask shop app and linked it to compliance checks in plain language.

## Scope used

- Target app: `webapplication/`
- Image tag used for scanning: `myshop-webapp:taske`
- SBOM format: CycloneDX JSON

## What I completed

1. Added container setup for the app:
   - `webapplication/Dockerfile`
   - `webapplication/.dockerignore`
2. Built the container image locally:
   - `docker build -t myshop-webapp:taske ./webapplication`
3. Generated dependency-level SBOM evidence:
   - `task-e/sbom-webapplication-cyclonedx.json`
   - `task-e/requirements-locked.txt`
   - `task-e/sbom-webapplication-locked-cyclonedx.json`
4. Generated image-level SBOM evidence:
   - `task-e/sbom-webapplication-image-cyclonedx.json`

## Evidence screenshots captured

- `task-e/evidence/task-e-evidence-01-docker-build.png`
- `task-e/evidence/task-e-evidence-02-syft-install-success.png`
- `task-e/evidence/task-e-evidence-03-syft-run-and-sbom-file-proof.png`

These screenshots show build success, Syft availability, and proof that the image SBOM file was actually generated.

## Why this matters for compliance (SSDF style)

SBOM gives software composition visibility. In practical terms, it helps with:

- tracking which third-party components are in the build
- checking those versions against vulnerability databases
- supporting audit/compliance evidence when asked what is inside the software
- speeding up response when a dependency CVE is published later

So even for a small coursework app, SBOM gives a repeatable supply-chain control instead of guessing dependencies manually.

## Short reflection

The dependency-only SBOM was quick to produce, but the image-level SBOM was more useful because it reflects what is actually packaged for runtime. Doing both gave better confidence and better evidence quality.

## Final status

Task E deliverables are in place and ready for submission polish.
