# Simulate a sports tournament

import csv
import sys
import random

# Number of simluations to run
N = 1000


def main():

    # Ensure correct usage
    if len(sys.argv) != 2:
        sys.exit("Usage: python tournament.py FILENAME")

    teams = []
    # TODO: Read teams into memory from file
    filename = sys.argv[1]

    # Opens file given in argv[1]
    with open(filename) as file:

        # Reads each line as a dictionary
        teams_reader = csv.DictReader(file)

        # For each line, copies it to a "team" dictionary, converting the "rating" value into an int, and appends it to "teams" list
        for line in teams_reader:
            team = {"team": line["team"], "rating": int(line["rating"])}
            teams.append(team)

    counts = {}
    # TODO: Simulate N tournaments and keep track of win counts
    for i in range(N):

        # Simulates tournament, and adds to the winner's counter in "counts" dictionary
        winner = simulate_tournament(teams)
        if winner in counts:
            counts[winner] += 1
        else:
            counts[winner] = 1

    # Print each team's chances of winning, according to simulation
    for team in sorted(counts, key=lambda team: counts[team], reverse=True):
        print(f"{team}: {counts[team] * 100 / N:.1f}% chance of winning")


def simulate_game(team1, team2):
    """Simulate a game. Return True if team1 wins, False otherwise."""
    rating1 = team1["rating"]
    rating2 = team2["rating"]
    probability = 1 / (1 + 10 ** ((rating2 - rating1) / 600))
    return random.random() < probability


def simulate_round(teams):
    """Simulate a round. Return a list of winning teams."""
    winners = []

    # Simulate games for all pairs of teams
    for i in range(0, len(teams), 2):
        if simulate_game(teams[i], teams[i + 1]):
            winners.append(teams[i])
        else:
            winners.append(teams[i + 1])

    return winners


def simulate_tournament(teams):
    """Simulate a tournament. Return name of winning team."""

    # Simulates a round, and returns the winners
    round_winners = simulate_round(teams)

    # Keep recursively simulating rounds until there's only one team in round_winners
    while len(round_winners) > 1:
        round_winners = simulate_round(round_winners)

    # Returns winner team's name
    return round_winners[0]["team"]


if __name__ == "__main__":
    main()
