#include <bits/stdc++.h>
using namespace std;

struct Point {
    int x, y;

    Point(int _x, int _y) : x(_x), y(_y) {}
};

bool isValid(int x, int y, int rows, int cols, vector<vector<bool>>& inactive) {
    return x >= 0 && x < rows && y >= 0 && y < cols && !inactive[x][y];
}

Point findMeetingPoint(int horseX, int horseY, int bishopX, int bishopY, vector<vector<bool>>& inactive) {
    int rows = inactive.size();
    int cols = inactive[0].size();

    vector<vector<bool>> visited(rows, vector<bool>(cols, false));

    queue<Point> horseQueue;
    queue<Point> bishopQueue;

    horseQueue.push(Point(horseX, horseY));
    bishopQueue.push(Point(bishopX, bishopY));

    while (!horseQueue.empty() || !bishopQueue.empty()) {
        if (!horseQueue.empty()) {
            int horseQueueSize = horseQueue.size();
            for (int i = 0; i < horseQueueSize; ++i) {
                Point horsePoint = horseQueue.front();
                horseQueue.pop();

                int x = horsePoint.x;
                int y = horsePoint.y;

                if (visited[x][y]) continue;
                visited[x][y] = true;

                if (x == bishopX && y == bishopY) {
                    return Point(x, y);
                }

                
                int horseMovesX[] = {-2, -1, 1, 2, 2, 1, -1, -2};
                int horseMovesY[] = {1, 2, 2, 1, -1, -2, -2, -1};

                for (int j = 0; j < 8; ++j) {
                    int newX = x + horseMovesX[j];
                    int newY = y + horseMovesY[j];

                    if (isValid(newX, newY, rows, cols, inactive)) {
                        horseQueue.push(Point(newX, newY));
                    }
                }
            }
        }

        if (!bishopQueue.empty()) {
            Point bishopPoint = bishopQueue.front();
            bishopQueue.pop();

            int x = bishopPoint.x;
            int y = bishopPoint.y;

            if (visited[x][y]) continue;
            visited[x][y] = true;

            
            for (int j = -1; j <= 1; j += 2) {
                for (int k = -1; k <= 1; k += 2) {
                    int newX = x + j;
                    int newY = y + k;

                    while (isValid(newX, newY, rows, cols, inactive)) {
                        bishopQueue.push(Point(newX, newY));
                        newX += j;
                        newY += k;
                    }
                }
            }
        }
    }

    
    return Point(-1, -1);
}

int main() {
    // Example
    int rows = 7;
    int cols = 7;

    vector<vector<bool>> inactive(rows, vector<bool>(cols, false));
    inactive[0][3] = true;
    inactive[2][0] = true;

    int horseX = 6, horseY = 6;
    int bishopX = 3, bishopY = 2;

    Point meetingPoint = findMeetingPoint(horseX, horseY, bishopX, bishopY, inactive);

    if (meetingPoint.x == -1 && meetingPoint.y == -1) {
        cout << "No meeting point found." << endl;
    } else {
        cout << "Meeting point: (" << meetingPoint.x << ", " << meetingPoint.y << ")" << endl;
    }

    return 0;
}