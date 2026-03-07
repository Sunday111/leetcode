#!/usr/bin/env python3
import re
from bs4 import BeautifulSoup
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


def problem_details_by_slug(slug: str) -> dict:
    query = """
    query questionData($titleSlug: String!) {
      question(titleSlug: $titleSlug) {
        questionId
        title
        codeSnippets {
          lang
          langSlug
          code
        }
        exampleTestcases
        sampleTestCase
        content
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
    return r.json()


def get_cpp_template(details: dict) -> str | None:
    snippets = details["data"]["question"]["codeSnippets"]

    for s in snippets:
        if s["langSlug"] == "cpp":
            return s["code"]

    return None


def get_method_name(details: dict) -> str | None:
    template = get_cpp_template(details)
    if template:
        end = template.find("(")
        assert end != -1
        begin = end
        while template[begin] != " ":
            begin -= 1
        return template[begin + 1 : end]


def get_sample_inputs(problem_details: dict):
    x: str = problem_details["data"]["question"]["exampleTestcases"]
    return x.splitlines()


def get_sample_outputs(problem_details: dict):
    soup = BeautifulSoup(problem_details["data"]["question"]["content"], "html.parser")

    outputs = []

    for block in soup.select("div.example-block"):
        p = block.find("p", string=lambda s: s and "Output:" in s)
        if not p:
            # handle the common <strong>Output:</strong> case
            strong = block.find("strong", string="Output:")
            if strong:
                span = strong.find_parent("p").find("span", class_="example-io")
                if span:
                    outputs.append(span.text.strip())
            continue

        span = p.find("span", class_="example-io")
        if span:
            outputs.append(span.text.strip())

    return outputs


def main():
    # code = fetch_cpp_template(slug)
    number = int(input("Problem number: "))
    index = request_all_problems()
    slug = get_slug_by_number(number, index)
    problem = problem_details_by_slug(slug)
    print(get_sample_inputs(problem))
    print(get_sample_outputs(problem))


if __name__ == "__main__":
    main()
