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
    for (const auto &article : articles) {
        cout << "Title: " << article.title << ", Score: " << article.score << endl;
    }
}

int main() {
    // Example articles
    vector<Article> articles = {
        {"Title 1", "Content of article 1"},
        {"Title 2", "Content of article 2"},
        {"Title 3", "Content of article 3"}
    };

    // Simulate comparisons
    updateScores(articles[0], articles[1], true);  // Article 1 wins over Article 2
    updateScores(articles[1], articles[2], false); // Article 3 wins over Article 2
    updateScores(articles[0], articles[2], true);  // Article 1 wins over Article 3

    // Rank the articles
    rankArticles(articles);

    // Display the ranked articles
    displayArticles(articles);

    return 0;
}
