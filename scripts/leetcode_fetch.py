#!/usr/bin/env python3
import re
import requests


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


def fetch_cpp_template(slug: str) -> str | None:
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


def main():
    title = input("Problem title: ").strip()

    slug = title_to_slug(title)
    print("Slug:", slug)

    code = fetch_cpp_template(slug)

    if code:
        print("\n--- C++ Template ---\n")
        print(code)
    else:
        print("C++ template not found.")


if __name__ == "__main__":
    main()
