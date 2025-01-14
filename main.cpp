#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>

using namespace std;

// Article structure to store title, content, and score
struct Article {
    string title;
    string content;
    int score = 1000; // Initial Elo score
};

// Calculate the probability of article A beating article B
double calculateProbability(int scoreA, int scoreB) {
    return 1.0 / (1.0 + pow(10, (scoreB - scoreA) / 400.0));
}

// Update scores based on the outcome of a comparison
void updateScores(Article &A, Article &B, bool A_wins, int K = 32) {
    double P_A = calculateProbability(A.score, B.score);
    double P_B = 1.0 - P_A;

    if (A_wins) {
        A.score += K * (1 - P_A);
        B.score += K * (0 - P_B);
    } else {
        A.score += K * (0 - P_A);
        B.score += K * (1 - P_B);
    }
}

// Sort articles based on their scores in descending order
void rankArticles(vector<Article> &articles) {
    sort(articles.begin(), articles.end(), [](const Article &a, const Article &b) {
        return a.score > b.score;
    });
}

// Display the articles and their scores
void displayArticles(const vector<Article> &articles) {
    cout << "Ranked Articles:\n";
    for (size_t i = 0; i < articles.size(); ++i) {
        cout << i + 1 << ". Title: " << articles[i].title
             << ", Score: " << articles[i].score << endl;
    }
}

// Function to dynamically input articles
void inputArticles(vector<Article> &articles) {
    int n;
    cout << "Enter the number of articles: ";
    cin >> n;
    cin.ignore(); // Clear the input buffer

    for (int i = 0; i < n; ++i) {
        Article article;
        cout << "Enter the title of article " << i + 1 << ": ";
        getline(cin, article.title);
        cout << "Enter the content of article " << i + 1 << ": ";
        getline(cin, article.content);
        articles.push_back(article);
    }
}

// Function to dynamically compare articles
void compareArticles(vector<Article> &articles) {
    int id1, id2;
    char result;

    cout << "Available articles:\n";
    for (size_t i = 0; i < articles.size(); ++i) {
        cout << i + 1 << ". " << articles[i].title << " (Score: " << articles[i].score << ")\n";
    }

    cout << "Select two articles to compare by entering their numbers:\n";
    cout << "Enter the number of the first article: ";
    cin >> id1;
    cout << "Enter the number of the second article: ";
    cin >> id2;

    if (id1 <= 0 || id1 > articles.size() || id2 <= 0 || id2 > articles.size() || id1 == id2) {
        cout << "Invalid selection. Try again.\n";
        return;
    }

    cout << "Who wins? Enter '1' for " << articles[id1 - 1].title
         << " or '2' for " << articles[id2 - 1].title << ": ";
    cin >> result;

    if (result == '1') {
        updateScores(articles[id1 - 1], articles[id2 - 1], true);
    } else if (result == '2') {
        updateScores(articles[id1 - 1], articles[id2 - 1], false);
    } else {
        cout << "Invalid input. Try again.\n";
        return;
    }

    rankArticles(articles);
    cout << "Scores updated and articles ranked successfully!\n";
}

int main() {
    vector<Article> articles;

    // Input articles
    inputArticles(articles);

    char choice;
    do {
        cout << "\nOptions:\n";
        cout << "1. Compare articles\n";
        cout << "2. Display rankings\n";
        cout << "3. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
        case '1':
            compareArticles(articles);
            break;
        case '2':
            displayArticles(articles);
            break;
        case '3':
            cout << "Exiting program. Goodbye!\n";
            break;
        default:
            cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != '3');

    return 0;
}
