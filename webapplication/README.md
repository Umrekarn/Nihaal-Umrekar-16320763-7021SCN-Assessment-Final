# My Shop — Flask web app (coursework / lab)

Small **Python Flask** app with **SQLite** (`database.db`). It behaves like a simple marketplace: **home + product list**, **register / login** (cookie stores `username`), **become a seller**, **add / edit / delete products**, **reviews** on product pages, and an **admin panel**.

`init_db.py` + `schema.sql` create the DB and seed sample products plus an **`admin` / `password`** admin user. The print line in `init_db.py` labels this as a **vulnerable** training setup — queries are built with **string concatenation**, passwords are stored **in plain text**, and HTML is built from DB fields with **no escaping**, which is typical for **security labs** (e.g. SQL injection / XSS) — **do not expose this on the public internet**.

## Run locally

```bash
cd webapplication
python init_db.py
pip install -r requirements.txt
flask --app app run
```

(On some setups `flask run` works if `FLASK_APP` is set; `flask --app app run` avoids that.)

Open **http://127.0.0.1:5000/** (same as the old `README.txt`).

## Layout

- **`app.py`** — Flask routes and handlers  
- **`schema.sql`** — SQLite schema  
- **`init_db.py`** — create DB + seed data  
- **`static/css/style.css`** — basic styling  

## Note

The older **`README.txt`** is still there if you use it; this **`README.md`** is the main description for the portfolio repo.
