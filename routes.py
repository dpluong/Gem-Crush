from app import app
from flask import render_template, request

# home page
@app.route('/')  # root : main page
def index():
    # by default, 'render_template' looks inside the folder 'template'
    with open('score.txt') as f:
        scores = []
        for line in f:
            if line:            
                line = int(line)
                scores.append(line)
    best_score = max(scores)
    return render_template('score.html', value = best_score)