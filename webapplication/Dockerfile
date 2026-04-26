FROM python:3.12-slim

WORKDIR /app

# Keep image minimal and deterministic for coursework builds.
COPY requirements.txt .
RUN pip install --no-cache-dir -r requirements.txt

COPY . .

EXPOSE 5000

CMD ["python", "-m", "flask", "--app", "app", "run", "--host=0.0.0.0", "--port=5000"]
