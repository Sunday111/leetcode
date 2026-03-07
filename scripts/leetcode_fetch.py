#!/usr/bin/env python3
import re
import requests
import json
from dataclasses import dataclass


GRAPHQL_URL = "https://leetcode.com/graphql"


def title_to_slug(title: str) -> str:
    """
    Convert '1888. Minimum Number of Flips to Make the Binary String Alternating'
    -> 'minimum-number-of-flips-to-make-the-binary-string-alternating'
    """
    title = re.sub(r"^\d+\.\s*", "", title)  # remove leading number
    slug = title.lower()
    slug = re.sub(r"[^a-z0-9]+", "-", slug)
    slug = slug.strip("-")
    return slug


def request_all_problems() -> dict:
    resp = requests.get("https://leetcode.com/api/problems/all/")
    resp.raise_for_status()
    return resp.json()


def find_problem_by_number(problem_number: int, problems_index: dict) -> str | None:
    for p in problems_index["stat_status_pairs"]:
        if p["stat"]["frontend_question_id"] == problem_number:
            return p

    return None


def get_slug_by_number(problem_number: int, problems_index: dict) -> str | None:
    p = find_problem_by_number(problem_number, problems_index)
    if p:
        return p["stat"]["question__title_slug"]
    return None


def cpp_template_by_slug(slug: str) -> str | None:
    query = """
    query questionData($titleSlug: String!) {
      question(titleSlug: $titleSlug) {
        codeSnippets {
          lang
          langSlug
          code
        }
      }
    }
    """

    r = requests.post(
        GRAPHQL_URL,
        json={
            "query": query,
            "variables": {"titleSlug": slug},
        },
    )

    r.raise_for_status()
    data = r.json()

    snippets = data["data"]["question"]["codeSnippets"]

    for s in snippets:
        if s["langSlug"] == "cpp":
            return s["code"]

    return None


def method_name_by_slug(slug: str) -> str | None:
    template = cpp_template_by_slug(slug)
    if template:
        end = template.find("(")
        assert end != -1
        begin = end
        while template[begin] != " ":
            begin -= 1
        return template[begin + 1 : end]


def main():
    # code = fetch_cpp_template(slug)
    number = int(input("Problem number: "))
    index = request_all_problems()
    problem = get_slug_by_number(number, index)
    method_name = method_name_by_slug(problem)
    print(f"Method name: {method_name}")


if __name__ == "__main__":
    main()
