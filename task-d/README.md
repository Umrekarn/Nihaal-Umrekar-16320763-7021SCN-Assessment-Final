# Task D - Dynamic analysis and exploit testing (local app)

For Task D I tested the local Flask shop app using OWASP ZAP and captured evidence of real web security issues.

Target app used:

- `http://127.0.0.1:5000/`
- source in `webapplication/`

Tool used:

- OWASP ZAP (desktop + HUD browser)

---

## 1) Test setup I used

1. Started the Flask app locally from `webapplication/`.
2. Opened ZAP and used **Manual Explore** with URL `http://127.0.0.1:5000/`.
3. Launched browser through ZAP (HUD enabled).
4. Browsed key routes to generate traffic:
   - home
   - login/register
   - product pages
   - admin panel (using seeded admin account)

This part was important because without enough traffic, active scan results are weak and sometimes miss stuff.

---

## 2) Evidence captured (matching the screenshots I took)

These are the screenshots I captured and what each one proves.

- `01-manual-explore-setup.png`
  - ZAP Manual Explore screen configured with local target URL.

- `02-browsing-through-zap.png`
  - Browser launched via ZAP, app loaded as admin (`Welcome to My Shop, admin!`).

- `03-sites-tree-history.png`
  - ZAP desktop with populated Sites tree and request history, confirming the app was actually proxied and crawled.

- `04-active-scan-started.png`
  - Active scan freshly started (early progress near start).

- `05-active-scan-progress.png`
  - Active scan running with higher progress and growing request count / alerts.

- `06-alerts-panel-xss.png`
  - Alert details for **Cross Site Scripting (Persistent)** shown in ZAP details pane.

- `07-alerts-panel-sqli.png`
  - Alert details for **SQL Injection** shown in ZAP details pane.

- `08-request-response-proof.png`
  - Specific request/response evidence (`POST /login`) shown with response details in ZAP.

- `09-impact-in-browser.png`
  - Browser-side impact screenshot showing payload-like content rendered in admin context.

I used these screenshots as the evidence chain from "scan setup" -> "scan run" -> "alert details" -> "request/response proof" -> "visible impact".

---

## 3) Key findings from the dynamic test

### A) Persistent XSS-style behaviour

ZAP flagged **Cross Site Scripting (Persistent)** and the app rendered payload-like content in admin-visible pages. This matches the app pattern where user content is directly inserted into HTML without proper escaping.

Impact:

- attacker-controlled content can be displayed in privileged views
- in a less controlled setup this can lead to session theft or forced actions

### B) SQL injection risk on auth flow

ZAP flagged **SQL Injection** around login-related traffic, and request/response behaviour showed server errors / abnormal responses under attack payloads.

This lines up with the code pattern where SQL strings are built with interpolation/f-strings and then executed.

Impact:

- possible login bypass or query manipulation
- exposure/modification risk for backend data

### C) Missing anti-CSRF controls

ZAP also flagged missing anti-CSRF protections. In this app that is believable because state-changing behaviour is available in routes that are not hardened with CSRF tokens.

Impact:

- forced requests can be triggered from another site if victim is already authenticated

---

## 4) Request/response proof summary

The `POST /login` history item and response details were captured as direct evidence that the target endpoint was tested through ZAP and returned behaviour consistent with the scanner findings.

I kept this because just showing the alerts tab alone is not enough for strong reporting.

---

## 5) Tool limitations and triage reflection

ZAP is useful but not magic. Some alerts are clearly useful, some are noisy, and some need manual checking before claiming real exploitability.

What I saw in practice:

- lots of low-level noise mixed with important alerts
- repeated alerts on related endpoints
- need to manually inspect request/response to avoid over-claiming

So I treated scanner output as a starting point, then used app behaviour and endpoint context to decide which findings were actually meaningful.

This is probably the biggest lesson from Task D: dynamic scanners help a lot, but judgement is still required.

---

## 6) Scope and ethics

All testing was done on my own local coursework target (`127.0.0.1`) with permission. No external systems were tested.

---

## 7) Suggested mitigation summary

If this app was hardened for real deployment, I would:

- parameterize all SQL queries
- use safe output encoding/template rendering for user content
- add CSRF tokens on state-changing routes
- avoid state changes on GET routes
- enforce stronger session/cookie security
- keep debug off outside local dev

These mitigation points also align with what was observed in Task B threat modelling.
