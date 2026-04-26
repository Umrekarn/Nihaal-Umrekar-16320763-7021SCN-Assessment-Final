# Task B - Threat modelling and SDLC (My Shop)

This report covers threat modelling for the Flask shop app in `webapplication/`.
The analysis is based directly on `app.py`, `schema.sql`, and `init_db.py`.

---

## 1) Trust boundaries and data flow

The browser side is the low-trust side. Users can change cookies, form input, and request paths before anything reaches the server.

The main flow in this app is:

- Browser sends request to Flask route
- Flask reads cookie/form/path input
- Flask runs SQL against SQLite
- SQLite returns rows
- Flask builds HTML response and sends it back

Routes that matter most for security in this project:

- `/` reads `username` cookie and uses it in a DB query
- `/login` and `/register` handle credentials
- `/product/<id>` loads products/reviews and accepts review posts
- `/add`, `/edit/<id>`, `/delete/<id>` change product data
- `/admin` exposes management actions

Trust boundaries to highlight:

- Internet -> Flask app
- Flask app -> SQLite database
- Database data -> HTML output in the browser

The `users` table stores password data as plain text in this lab setup, and the seed script adds `admin/password`, so this is intentionally a weak training target.

### Diagram set used in this task

Level 1 (context and trust boundaries):

`task-b/diagrams/level-1-dfd-my-shop-trust-boundaries.png`

Level 2 (auth + product flow decomposition):

`task-b/diagrams/level-2-dfd-auth-and-product-flow.png`

Level 3 (admin/review control decomposition):

`task-b/diagrams/level-3-dfd-admin-and-review-control-flow.png`

What changed between levels:

- Level 1 keeps the broad architecture and boundary view.
- Level 2 breaks normal user and product paths into internal process groups.
- Level 3 zooms into high-risk control points (admin role checks, review handling, edit/delete controls).

---

## 2) STRIDE analysis for this codebase

### Spoofing

The app uses a plain `username` cookie as the identity signal after login. The same cookie value is trusted across multiple routes. If cookie integrity is not protected, identity spoofing is possible.

The login query is also built from string interpolation, which creates an authentication bypass risk through SQL injection patterns.

### Tampering

Most database queries are built with f-strings using user-controlled values.
That opens the door to SQL injection and unauthorised data changes.

The app also renders product/review content into HTML directly, so stored content can tamper with page behaviour (XSS risk).

`/delete/<id>` is a GET route that performs a state change, which increases CSRF risk.

### Repudiation

There is no proper audit trail for actions like login, product changes, privilege changes, and deletes.
Without logs, it is difficult to prove who did what.

### Information disclosure

Passwords are stored in plain text in the database schema used here.

Debug mode is enabled in the app entrypoint, which can expose too much runtime detail if not limited to local development.

Registration feedback can also leak whether a username already exists.

### Denial of service

There is no rate limiting on login/register/review routes.

The home page pulls all products and builds one large response string, which can become inefficient as data grows.

### Elevation of privilege

Admin access checks depend on cookie identity plus DB role flag.
If identity handling is weak, privilege boundaries become weak too.

Also, edit/delete ownership checks are not strict enough for seller-to-seller isolation.

---

## 3) Security requirements / mitigations

If this app were being hardened for real use, these are the requirements I would apply:

- Replace raw cookie identity with proper session handling and secure cookie settings.
- Hash passwords (`generate_password_hash` / `check_password_hash` or Argon2); never store plain text.
- Replace all f-string SQL with parameterised queries (`?` placeholders).
- Use template rendering with escaping for all user-provided content.
- Move state-changing actions to POST/DELETE and apply CSRF protection.
- Enforce ownership checks on edit/delete, not just broad role checks.
- Add structured audit logging for security-relevant events.
- Add basic rate limiting and pagination.
- Keep debug off outside local development and load secrets from environment config.

---

## 4) SDLC reflection

The biggest lesson in this task is that security decisions are easier and cheaper during design.

If trust boundaries and data flows are mapped early, it is much less likely that unsafe patterns (string-built SQL, weak identity handling, unescaped output) spread through multiple routes.

A practical SDLC view for this project:

- Design: define boundaries and secure defaults
- Build: use framework-safe patterns from the start
- Test: combine static and dynamic testing
- Deploy: manage secrets, logs, and runtime config properly

So this task is not just a vulnerability list. It shows how design choices drive implementation quality and later security effort.

---

## Scope and ethics

This analysis is for authorised local coursework testing only.

---

## References

- 7021SCN lecture/lab material (STRIDE and secure coding topics)
- OWASP guidance for SQL injection and XSS
- CWE references relevant to identified issues

(References will be formatted to the final required citation style before submission.)
