from flask import app, url_for, redirect, request
from markupsafe import escape
app = app.Flask(__name__)


@app.route('/')
def index():
    user_agent = request.headers.get('User-Agent')
    return '<h1>your browser is %s</h1>' % user_agent


@app.route('/user/<string:name>')
def user(name):
    return '<h2>hello, %s!</h2>' % name


@app.route('/post/<int:post_id>')
def show_id(post_id):
    return '<h2>your id %d!</h2>' % post_id


@app.route('/path/<path:subpath>')
def show_subpath(subpath):
    return '<h2>your path %s!</h2>' % escape(subpath)


@app.route('/search')
def search():
    return redirect('http://www.baidu.com')


with app.test_request_context():
    print(url_for('index'))
    print(url_for('user', name="test"))
    print(url_for('show_subpath', subpath='hellpath'))
    print(url_for('static', filename='test.css'))


@app.route('/login', methods=['GET', 'POST'])
def login():
    if request.method == 'POST':
        return do_the_login()
    else:
        return show_login_form()


# if __name__ == '__main__':
#    app.run(debug=True)
